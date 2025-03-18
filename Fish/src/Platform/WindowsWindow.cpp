#include "fishpch.h"
#include "WindowsWindow.h"

namespace Fish
{
	static bool s_GLFWInitialized = false;

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
			//TODO:glfwTerminate on system shutdown
			int success = glfwInit();
			//glfwInit() 函数会返回一个整数值来指示初始化是否成功
			FISH_CORE_ASSERT(success, "Could Not Initialize GLFW!");
			//如果glfwInit()返回值为1，即初始化成功
			//success = x = 1，则 !x为false， if不成立（Core.h）
			//当初始化失败时，if成立，输出Assertion Failed : Could Not Initialize GLFW!


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