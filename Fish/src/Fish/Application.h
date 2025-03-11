#pragma once

#include "Core.h"

namespace Fish
{
	class FISH_API Application
	{

	public:
		Application();
		virtual ~Application();
		//多态：分为       静态多态：函数重载、运算符重载       和       动态多态：派生类和虚函数
		//动态多态:函数地址晚绑定    
		//条件：     1.有继承关系    2.子类重写父类虚函数   3.父类指针或引用指向子类对象
		//原理：vfptr和vftable
		// 纯虚函数 抽象类
		// 
		//父类指针在析构的时候不会调用子类析构函数，导致子类如果有堆区属性，无法析构，内存泄露
		//解决：父类析构函数改成虚析构
		//纯虚析构需要有声明，也需要有实现
		// 因为父类可能有属性构造在堆区，需要释放
		// 与纯虚函数不同，纯虚函数=0就完事了，纯虚析构需要再类外实现
		//有了纯虚析构也属于抽象类 
		//

		void run();
	};

	//To be defined in the CLIENT
	Application* CreateApplication();

}
