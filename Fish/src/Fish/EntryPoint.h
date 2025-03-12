#pragma once

#ifdef FISH_PLATFORM_WINDOWS

extern Fish::Application* Fish::CreateApplication();
//关键字 extern 表示该函数的定义在另一个编译单元（如 .cpp 文件）中，当前文件只是声明它的存在，告诉编译器“稍后链接时会找到具体实现”。

//其实自己本来有一个疑惑，自己这时已经理清了整个代码的互相引用的框架，所有代码都在SandboxApp里运行
//那为什么还要写一次声明
//比较粗暴的目前理解：引用可以理解成把被引用的这段代码原封不动写在引用位置
//既然如此，那么在SandboxApp.cpp中，main函数的位置在实现CreateApplication函数的上面，就需要声明一下



int main(int argc, char** argv)
//带参数的main函数可以接受命令行参数
//前者为参数计数（Argument Count），表示命令行参数的总数量（包括程序名本身）；
//后者为参数值数组（Argument Values），存储所有命令行参数的字符串指针数组。	
{
	Fish::Log::Init();
	//Init为静态成员函数，故可以不实例化类，直接这样调用
	//CPP笔记 P7 32条
	FISH_CORE_WARN("Initialized Log!");
	int a = 5;
	FISH_INFO("Hello!  var = {0}",a);

	auto app = Fish::CreateApplication();
	app->run();
	delete app;

}



#endif