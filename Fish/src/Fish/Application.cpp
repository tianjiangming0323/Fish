//类的分文件编写
//在使用时只包含头文件即可
//cpp 笔记 P5第25条
#include "fishpch.h"    
//每个cpp文件中都需要包含预编译头文件，且需要第一个包含
#include "Application.h"

#include "Fish/Log.h"

//#include <GLFW/glfw3.h>
#include <glad/glad.h>
//#include "Fish/Input.h"


namespace Fish
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
//定义了一个宏 BIND_EVENT_FN(x)，用于将 Application 类的成员函数 x 绑定为一个可调用对象，使其能够适配需要函数指针或函数对象的接口（例如事件回调）
//std::bind将函数/成员函数与参数绑定，生成一个新的可调用对象
//三个参数分别为：
//要绑定的函数（如成员函数指针 &Application::x）            
//预先绑定的参数（如 this）        
//占位符（如 _1），表示生成的函数对象在被调用时需要接收一个参数，即OnEvent需要一个参数

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		FISH_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		//应用了单例模式

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		//SetEventCallback 输入为一个函数，该函数的输入为Event&，返回值为void
		//将该函数设置为回调函数
		//即WindowsWindow.cpp中，每个GLFW Callbacks中的data.EventCallback(event)  ==  OnEvent(event)
		
	}

	Application::~Application()
	{


	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();

	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		//Dispatch函数接受一个参数为T&，返回值为bool的函数func为参数
		//首先判断e和T的类型是否匹配
		//若匹配则利用func对e进行处理

		//在这里显式指定类型方法调用Dispatch，即T&为WindowCloseEvent

		//FISH_CORE_TRACE("{0}", e.ToString());
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			//m_LayerStack 的遍历顺序从末尾（最上层）到开头（最底层），符合“上层 Layer 优先处理事件”的设计
			if (e.Handled)
				break;
			// 若某层调用 e.Handled = true，事件停止传播，后续层不再处理
		}

	}
	//OnEvent仅对WindowClose有操作，为啥在实际应用中能改变size
	//改变size的逻辑在于：glfwSetWindowSizeCallback回调函数中WindowData& data是现在这个窗口data的引用
	//在回调函数中改变尺寸即可改变实际视口的窗口大小
	//而其他的操作主要是打印Log
	// 
	//Dispatch函数接受一个参数为T&，返回值为bool的函数func为参数
	//首先判断e和T的类型是否匹配
	//若匹配则利用func对e进行处理


	void Application::run()
	{
		/*WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			FISH_TRACE(e.ToString());
		}

		if (e.IsInCategory(EventCategoryInput))
		{
			FISH_TRACE(e.ToString());
		}
		while (true);*/

		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			//设置清除颜色缓冲时使用的颜色
			glClear(GL_COLOR_BUFFER_BIT);
			//清除当前帧缓冲区的指定部分（这里是颜色缓冲区）
			//GL_DEPTH_BUFFER_BIT：清除深度缓冲区（用于3D深度测试）。
			//GL_STENCIL_BUFFER_BIT：清除模板缓冲区（用于模板测试）。

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();
			//先Example再ImGui

			/*auto [x, y] = Input::GetMousePosition();
			FISH_CORE_TRACE("{0},{1}", x, y);*/

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}

