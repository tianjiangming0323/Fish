#pragma once

#ifdef FISH_PLATFORM_WINDOWS

extern Fish::Application* Fish::CreateApplication();
//关键字 extern 表示该函数的定义在另一个编译单元（如 .cpp 文件）中，当前文件只是声明它的存在，告诉编译器“稍后链接时会找到具体实现”。

int main(int argc, char** argv)
//带参数的main函数可以接受命令行参数
//前者为参数计数（Argument Count），表示命令行参数的总数量（包括程序名本身）；
//后者为参数值数组（Argument Values），存储所有命令行参数的字符串指针数组。	
{
	auto app = Fish::CreateApplication();
	app->run();
	delete app;

}



#endif