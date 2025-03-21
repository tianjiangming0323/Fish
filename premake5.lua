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
--IncludeDir = {} �Ǵ�����һ���յ� Lua ��table���������洢��ͬģ����İ���Ŀ¼��
IncludeDir = {}
IncludeDir["GLFW"] = "Fish/vendor/GLFW/include"
IncludeDir["Glad"] = "Fish/vendor/Glad/include"
IncludeDir["ImGui"] = "Fish/vendor/imgui"

include "Fish/vendor/GLFW"
include "Fish/vendor/Glad"
include "Fish/vendor/imgui"

project "Fish"
	location "Fish"
	kind "SharedLib"         --����Ϊ��̬��
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")                   --.. XX .. ��..���ַ������ӷ�
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
		--%{IncludeDir.GLFW}��ʾҪ��ȡ�� IncludeDir �м�Ϊ "GLFW" ��Ԫ��ֵ
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
		--staticruntime "On"    --�Ƿ�̬��������ʱ�⣨dll���Ե��ļ���Ҫ�򿪣�
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
			--("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")   --�㲻���ˣ�ֱ��F5���оͻᱨ���ȱ��������о�û����    ���䣺����Ҫ��Sandbox.cpp������У�������cpp�ļ���Ч
			--����ԭ����bin/Debug/Sandboxû�������ļ��У����Ǳ����һ����֪���ļ�
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