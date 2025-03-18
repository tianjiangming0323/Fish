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
			//glfwInit() �����᷵��һ������ֵ��ָʾ��ʼ���Ƿ�ɹ�
			FISH_CORE_ASSERT(success, "Could Not Initialize GLFW!");
			//���glfwInit()����ֵΪ1������ʼ���ɹ�
			//success = x = 1���� !xΪfalse�� if��������Core.h��
			//����ʼ��ʧ��ʱ��if���������Assertion Failed : Could Not Initialize GLFW!


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