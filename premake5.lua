workspace "Fish"          
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"             --Debug-windows-x86_64

--include directories relative to root floder (solution directory)
--IncludeDir = {} 是创建了一个空的 Lua 表（table），用来存储不同模块或库的包含目录。
IncludeDir = {}
IncludeDir["GLFW"] = "Fish/vendor/GLFW/include"
IncludeDir["Glad"] = "Fish/vendor/Glad/include"
IncludeDir["ImGui"] = "Fish/vendor/imgui"

include "Fish/vendor/GLFW"
include "Fish/vendor/Glad"
include "Fish/vendor/imgui"

project "Fish"
	location "Fish"
	kind "SharedLib"         --类型为动态库
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")                   --.. XX .. 中..是字符串连接符
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "fishpch.h"
	pchsource "Fish/src/fishpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		--%{IncludeDir.GLFW}表示要获取表 IncludeDir 中键为 "GLFW" 的元素值
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		--staticruntime "On"    --是否静态链接运行时库（dll属性的文件需要打开）
		systemversion "latest"   

		defines
		{
			"FISH_PLATFORM_WINDOWS",
			"FISH_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			--("IF NOT EXIST ../bin/" .. outputdir .. "/Sandbox mkdir ../bin/" .. outputdir .. "/Sandbox"),
			--("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")   --搞不懂了，直接F5运行就会报错；先编译再运行就没问题    补充：必须要在Sandbox.cpp编译才行，其他的cpp文件无效
			--报错原因在bin/Debug/Sandbox没有生成文件夹，而是变成了一个不知名文件
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "FISH_DEBUG"
		symbols "On"
		buildoptions "/utf-8"
		runtime "Debug"


	filter "configurations:Release"
		defines "FISH_RELEASE"
		optimize "On"
		buildoptions "/utf-8"
		runtime "Release"

	filter "configurations:Dist"
		defines "FISH_DIST"
		optimize "On"
		buildoptions "/utf-8"
		runtime "Release"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Fish/vendor/spdlog/include",
		"Fish/src"
	}

	links
	{
		"Fish"
	}

	filter "system:windows"
		cppdialect "C++17"
		--staticruntime "On"
		systemversion "latest"

		defines
		{
			"FISH_PLATFORM_WINDOWS"	
		}
		

	filter "configurations:Debug"
		defines "FISH_DEBUG"
		symbols "On"
		buildoptions "/utf-8"
		runtime "Debug"


	filter "configurations:Release"
		defines "FISH_RELEASE"
		optimize "On"
		buildoptions "/utf-8"
		runtime "Release"

	filter "configurations:Dist"
		defines "FISH_DIST"
		optimize "On"
		buildoptions "/utf-8"
		runtime "Release"