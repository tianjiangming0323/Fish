//��ķ��ļ���д
//��ʹ��ʱֻ����ͷ�ļ�����
//cpp �ʼ� P5��25��
#include "fishpch.h"    
//ÿ��cpp�ļ��ж���Ҫ����Ԥ����ͷ�ļ�������Ҫ��һ������
#include "Application.h"

#include "Fish/Log.h"

//#include <GLFW/glfw3.h>
#include <glad/glad.h>
//#include "Fish/Input.h"


namespace Fish
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
//������һ���� BIND_EVENT_FN(x)�����ڽ� Application ��ĳ�Ա���� x ��Ϊһ���ɵ��ö���ʹ���ܹ�������Ҫ����ָ���������Ľӿڣ������¼��ص���
//std::bind������/��Ա����������󶨣�����һ���µĿɵ��ö���
//���������ֱ�Ϊ��
//Ҫ�󶨵ĺ��������Ա����ָ�� &Application::x��            
//Ԥ�Ȱ󶨵Ĳ������� this��        
//ռλ������ _1������ʾ���ɵĺ��������ڱ�����ʱ��Ҫ����һ����������OnEvent��Ҫһ������

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		FISH_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		//Ӧ���˵���ģʽ

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		//SetEventCallback ����Ϊһ���������ú���������ΪEvent&������ֵΪvoid
		//���ú�������Ϊ�ص�����
		//��WindowsWindow.cpp�У�ÿ��GLFW Callbacks�е�data.EventCallback(event)  ==  OnEvent(event)
		
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
		//Dispatch��������һ������ΪT&������ֵΪbool�ĺ���funcΪ����
		//�����ж�e��T�������Ƿ�ƥ��
		//��ƥ��������func��e���д���

		//��������ʽָ�����ͷ�������Dispatch����T&ΪWindowCloseEvent

		//FISH_CORE_TRACE("{0}", e.ToString());
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			//m_LayerStack �ı���˳���ĩβ�����ϲ㣩����ͷ����ײ㣩�����ϡ��ϲ� Layer ���ȴ����¼��������
			if (e.Handled)
				break;
			// ��ĳ����� e.Handled = true���¼�ֹͣ�����������㲻�ٴ���
		}

	}
	//OnEvent����WindowClose�в�����Ϊɶ��ʵ��Ӧ�����ܸı�size
	//�ı�size���߼����ڣ�glfwSetWindowSizeCallback�ص�������WindowData& data�������������data������
	//�ڻص������иı�ߴ缴�ɸı�ʵ���ӿڵĴ��ڴ�С
	//�������Ĳ�����Ҫ�Ǵ�ӡLog
	// 
	//Dispatch��������һ������ΪT&������ֵΪbool�ĺ���funcΪ����
	//�����ж�e��T�������Ƿ�ƥ��
	//��ƥ��������func��e���д���


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
			//���������ɫ����ʱʹ�õ���ɫ
			glClear(GL_COLOR_BUFFER_BIT);
			//�����ǰ֡��������ָ�����֣���������ɫ��������
			//GL_DEPTH_BUFFER_BIT�������Ȼ�����������3D��Ȳ��ԣ���
			//GL_STENCIL_BUFFER_BIT�����ģ�建����������ģ����ԣ���

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();
			//��Example��ImGui

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

