#pragma once

#include "Core.h"

#include "Window.h"
#include "Fish/LayerStack.h"
#include "Fish/Events/Event.h"
#include "Fish/Events/ApplicationEvent.h"

#include "Fish/ImGui/ImGuiLayer.h"


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
		// 与纯虚函数不同，纯虚函数=0就完事了，纯虚析构需要在类外实现
		//有了纯虚析构也属于抽象类 
		//

		void run();

		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
		//s_Instance为类指针，返回解引用
		
	private:

		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		//m_Window拥有对窗口对象的唯一所有权，当m_Window被销毁时，窗口对象也会被自动销毁，这有助于管理资源的生命周期，避免内存泄漏
		//unique_ptr 不能被复制（拷贝构造函数和赋值运算符被删除），但可以通过 std::move 移动所有权。
		//当 m_Window 离开作用域（如所在对象被销毁），或显式调用 reset() 时，unique_ptr 会自动调用 delete 释放其指向的 Window 对象。

		

		ImGuiLayer* m_ImGuiLayer;

		bool m_Running = true;
		LayerStack m_LayerStack;

	private:
		static Application* s_Instance;
		//Application被设置成了单例类
		//确保一个类只有一个实例，并提供一个全局访问点，方便其他代码获取该实例。它常用于管理全局资源（如配置、数据库连接、日志系统等）
		//虽然此类中构造函数是public
		//但可以将构造函数private，这样就禁止了利用new等关键字进行外部实例化
		//单例类想要与外界进行数据交换就只能通过静态函数Get()实现
	};

	//To be defined in the CLIENT
	Application* CreateApplication();

}
