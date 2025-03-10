#pragma once


#ifdef FISH_PLATFORM_WINDOWS
	#ifdef FISH_BUILD_DLL
		#define FISH_API __declspec(dllexport)
	#else
		#define FISH_API __declspec(dllimport)
	#endif
#else
	#error FISH only support Windows!
#endif