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
			//glfwInit() �����᷵��һ������ֵ��ָʾ��ʼ���Ƿ�ɹ�
			FISH_CORE_ASSERT(success, "Could Not Initialize GLFW!");
			//���glfwInit()����ֵΪ1������ʼ���ɹ�
			//success = x = 1���� !xΪfalse�� if��������Core.h��
			//����ʼ��ʧ��ʱ��if���������Assertion Failed : Could Not Initialize GLFW!

			glfwSetErrorCallback(GLFWErrorCallback);


			s_GLFWInitialized = true;

			
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		//������� nullptr����ʾ����ģʽ���У��Ҳ����������ڹ��� OpenGL ��Դ������������������
		glfwMakeContextCurrent(m_Window);
		//�����İ���������OpenGL��״̬��Ϣ������������ɫ�����������ȡ����л�������ʱ��ʵ���������л���ͬ��״̬���ϡ�ÿ�����ڶ��������Լ��������ģ�����ȷ������������Ⱦ���ض����ڵĹؼ�
		//glfwMakeContextCurrent(m_Window)�� OpenGL �����ģ�Context�� �󶨵���ǰ�̣߳���������ָ���Ĵ��ڣ�m_Window��
		//ֻ�а������ĺ���ܵ���OpenGL����������Application.cpp�е�glClearColor(1, 0, 1, 1)��glClear(GL_COLOR_BUFFER_BIT)

		glfwSetWindowUserPointer(m_Window, &m_Data);
		//���Զ������ݣ�m_Data ��ָ�룩���ӵ����ڶ���
		//�ڻص�������ֱ�ӷ����봰����ص�����
		SetVSync(true);
		//���ô�ֱͬ��Vertical Synchronization, VSync
		//���Կ������֡�ʣ�FPS��������ʾ��ˢ���ʣ��� 60Hz��ʱ����ʾ��������һ��ˢ����������ʾ��֡��ͬ�Ļ��棬���»���˺��
		//���� VSync ���Կ���ȴ���ʾ���Ĵ�ֱ�հ��ڣ�VBlank�����ύ��֡��ȷ��ÿ��ˢ��ֻ��ʾ������һ֡




		//Set GLFW Callbacks
		// 
		//lambda���ʽ
		// [�����б�] (�����б�) -> �������� { ������ }
		// Lambda ���ʽ��һ�������������﷨�ǣ������ڴ�����ֱ�Ӷ����������ĺ�������
	
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			//glfwGetWindowUserPointer����ֵ����Ϊvoid*
			//ǿת��WindowData* ���ͣ��ٽ����õõ�WindowData����
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
			//���ڽ��¼����ݸ�Ӧ�ó�����¼�ϵͳ
		});
		//�Լ�һֱ�и��ɻ󣺴�ʱEventCallbackδ���壬data.EventCallback(event)զ���е�
		//���ͣ�����ֻ�ǶԻص�������ע�ᣬlambda���ʽ��ʱ����ִ��
		//ֻ���ڴ��ڳߴ�ʵ�ʸı��ʱ�򣬲Ż����

		//�޲����lambda���ʽ�ſ�����ʽת��Ϊc����ָ��
		//����Ҫʹ��ָ��Ȼ�ȡ�ⲿ����
		//�����ǲ���ĺ���
		
		//int a = 10;
		//int b = 20;
		// ��ֵ���� a�������ò��� b
		//auto lambda1 = [a, &b]() {
		//	std::cout << a + b << std::endl; // a �ǿ�����b ������
		//	b++; // �޸Ļ�Ӱ���ⲿ�� b
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
		//�����û�����ʹ����¼������ֳ��򽻻���
		glfwSwapBuffers(m_Window);
		//�л���Ⱦ����������ʾ����֡�Ļ���
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