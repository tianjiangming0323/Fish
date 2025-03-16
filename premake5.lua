workspace "Fish"          
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"             --Debug-windows-x86_64

project "Fish"
	location "Fish"
	kind "SharedLib"         --����Ϊ��̬��
	language "C++"

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
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"    --�Ƿ�̬��������ʱ�⣨dll���Ե��ļ���Ҫ�򿪣�
		systemversion "latest"   

		defines
		{
			"FISH_PLATFORM_WINDOWS",
			"FISH_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")   --�㲻���ˣ�ֱ��F5���оͻᱨ���ȱ��������о�û����
			--����ԭ����bin/Debug/Sandboxû�������ļ��У����Ǳ����һ����֪���ļ�
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