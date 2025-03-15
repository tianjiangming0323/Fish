#pragma once
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"
#include <memory>

namespace Fish
{
	class FISH_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger;  }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
		//inline 内联函数 是一种“建议”编译器优化函数的调用方式
		//通过将函数定义为inline，编译器可以尝试将函数的代码直接插入到每个调用点，而不是通过常规的函数调用来执行
		//对于类内的成员函数，若在类内定义，则默认为inline；若在类外定义，则需要显式添加inline
		//inline常定义在头文件中，可在头文件中直接写函数定义
		//不要对复杂函数使用inline

		//static：静态成员函数——只能访问静态成员变量（CPP笔记 P7 32条）

		//std::shared_ptr是 C++ 标准库（STL）中的一个智能指针类型，属于 <memory> 头文件。
		//它用于自动管理动态分配的内存，通过引用计数机制实现多个指针共享同一块内存的所有权，从而避免内存泄漏
		//<>里是指针指向的内容的数据类型（int、float等）

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
		//静态成员变量：所有对象共享同一份数据（CPP笔记 P7 32条）
		// 编译阶段分配内存
		// 类内声明，类外初始化
		//比如定义了两个Log类实例，log1和log2，那么它们的该变量属于同一内存

	};

}


//Core Log Macros
#define FISH_CORE_TRACE(...)		::Fish::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define FISH_CORE_INFO(...)			::Fish::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FISH_CORE_WARN(...)			::Fish::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FISH_CORE_ERROR(...)		::Fish::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FISH_CORE_FATAL(...)		::Fish::Log::GetCoreLogger()->fatal(__VA_ARGS__)


//Core Log Macros
#define FISH_TRACE(...)				::Fish::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FISH_INFO(...)				::Fish::Log::GetClientLogger()->info(__VA_ARGS__)
#define FISH_WARN(...)				::Fish::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FISH_ERROR(...)				::Fish::Log::GetClientLogger()->error(__VA_ARGS__)
#define FISH_FATAL(...)				::Fish::Log::GetClientLogger()->fatal(__VA_ARGS__)

//参数__VA_ARGS__为可变参数宏，允许传递任意数量和类型的参数
//两个连续的冒号 :: 出现在最前面时，表示从全局命名空间（Global Namespace）开始解析作用域。
