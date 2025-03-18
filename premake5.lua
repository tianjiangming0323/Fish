workspace "Fish"          
	architecture "x64"

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

include "Fish/vendor/GLFW"

project "Fish"
	location "Fish"
	kind "SharedLib"         --类型为动态库
	language "C++"

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
		"%{IncludeDir.GLFW}"
		--%{IncludeDir.GLFW}表示要获取表 IncludeDir 中键为 "GLFW" 的元素值
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"    --是否静态链接运行时库（dll属性的文件需要打开）
		systemversion "latest"   

		defines
		{
			"FISH_PLATFORM_WINDOWS",
			"FISH_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")   --搞不懂了，直接F5运行就会报错；先编译再运行就没问题
			--报错原因在bin/Debug/Sandbox没有生成文件夹，而是变成了一个不知名文件
		}

	filter "configurations:Debug"
		defines "FISH_DEBUG"
		symbols "On"
		buildoptions "/utf-8"


	filter "configurations:Release"
		defines "FISH_RELEASE"
		optimize "On"
		buildoptions "/utf-8"

	filter "configurations:Dist"
		defines "FISH_DIST"
		optimize "On"
		buildoptions "/utf-8"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"FISH_PLATFORM_WINDOWS"	
		}
		

	filter "configurations:Debug"
		defines "FISH_DEBUG"
		symbols "On"
		buildoptions "/utf-8"


	filter "configurations:Release"
		defines "FISH_RELEASE"
		optimize "On"
		buildoptions "/utf-8"

	filter "configurations:Dist"
		defines "FISH_DIST"
		optimize "On"
		buildoptions "/utf-8"