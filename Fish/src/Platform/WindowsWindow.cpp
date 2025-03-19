#include "fishpch.h"
#include "WindowsWindow.h"

#include "Fish/Events/ApplicationEvent.h"
#include "Fish/Events/MouseEvent.h"
#include "Fish/Events/KeyEvent.h"

namespace Fish
{
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		FISH_CORE_ERROR("GLFW Error ({0}) : {1}", error, description);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		ShutDown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Height = props.Height;
		m_Data.Width = props.Width;

		FISH_CORE_INFO("Creating Window {0}  {1},{2}", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			
			int success = glfwInit();
			//glfwInit() 函数会返回一个整数值来指示初始化是否成功
			FISH_CORE_ASSERT(success, "Could Not Initialize GLFW!");
			//如果glfwInit()返回值为1，即初始化成功
			//success = x = 1，则 !x为false， if不成立（Core.h）
			//当初始化失败时，if成立，输出Assertion Failed : Could Not Initialize GLFW!

			glfwSetErrorCallback(GLFWErrorCallback);


			s_GLFWInitialized = true;

			
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		//最后两个 nullptr：表示窗口模式运行，且不与其他窗口共享 OpenGL 资源（如纹理、缓冲区）。
		glfwMakeContextCurrent(m_Window);
		//上下文包含了所有OpenGL的状态信息，比如纹理、着色器、缓冲区等。当切换上下文时，实际上是在切换不同的状态集合。每个窗口都可以有自己的上下文，而正确绑定上下文是渲染到特定窗口的关键
		//glfwMakeContextCurrent(m_Window)将 OpenGL 上下文（Context） 绑定到当前线程，并关联到指定的窗口（m_Window）
		//只有绑定上下文后才能调用OpenGL函数（比如Application.cpp中的glClearColor(1, 0, 1, 1)和glClear(GL_COLOR_BUFFER_BIT)

		glfwSetWindowUserPointer(m_Window, &m_Data);
		//将自定义数据（m_Data 的指针）附加到窗口对象
		//在回调函数中直接访问与窗口相关的数据
		SetVSync(true);
		//设置垂直同步Vertical Synchronization, VSync
		//当显卡输出的帧率（FPS）高于显示器刷新率（如 60Hz）时，显示器可能在一次刷新周期内显示两帧不同的画面，导致画面撕裂
		//开启 VSync 后，显卡会等待显示器的垂直空白期（VBlank）再提交新帧，确保每次刷新只显示完整的一帧




		//Set GLFW Callbacks
		// 
		//lambda表达式
		// [捕获列表] (参数列表) -> 返回类型 { 函数体 }
		// Lambda 表达式是一种匿名函数的语法糖，允许在代码中直接定义轻量级的函数对象
	
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			//glfwGetWindowUserPointer返回值类型为void*
			//强转成WindowData* 类型，再解引用得到WindowData对象
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
			//用于将事件传递给应用程序的事件系统
		});
		//自己一直有个疑惑：此时EventCallback未定义，data.EventCallback(event)咋运行的
		//解释：这里只是对回调函数的注册，lambda表达式此时不会执行
		//只有在窗口尺寸实际改变的时候，才会调用

		//无捕获的lambda表达式才可以隐式转换为c函数指针
		//故需要使用指针等获取外部数据
		//以下是捕获的含义
		
		//int a = 10;
		//int b = 20;
		// 按值捕获 a，按引用捕获 b
		//auto lambda1 = [a, &b]() {
		//	std::cout << a + b << std::endl; // a 是拷贝，b 是引用
		//	b++; // 修改会影响外部的 b
		//	};

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);

		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				
			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
			}
		});


		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}

			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});
		//mouse moved event

	}

	void WindowsWindow::ShutDown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		//处理用户输入和窗口事件，保持程序交互性
		glfwSwapBuffers(m_Window);
		//切换渲染缓冲区，显示最新帧的画面
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
		m_Data.VSync = enabled;

	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
}