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

#ifdef FISH_ENABLE_ASSETRTS
	#define FISH_ASSERT(x,...) {if(!x) {FISH_ERROR("Assertion Failed : {0}", __VA_ARGS__);__debugbreak();}}
	#define FISH_Core_ASSERT(x,...) {if(!x) {FISH_Core_ERROR("Assertion Failed : {0}", __VA_ARGS__);__debugbreak();}}
#else
	#define FISH_ASSERT(x,...)
	#define FISH_CORE_ASSERT(x,...)
#endif
//调试模式下FISH_ENABLE_ASSERTS为定义
//发布模式下未定义
//__debugbreak()为MSVC 特有的内置函数，用于触发调试断点


#define BIT(x) (1 << x)