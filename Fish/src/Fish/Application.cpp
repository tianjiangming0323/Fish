//��ķ��ļ���д
//��ʹ��ʱֻ����ͷ�ļ�����
//cpp �ʼ� P5��25��
#include "fishpch.h"    
//ÿ��cpp�ļ��ж���Ҫ����Ԥ����ͷ�ļ�������Ҫ��һ������
#include "Application.h"
#include "Fish/Events/ApplicationEvent.h"
#include "Fish/Log.h"

#include <GLFW/glfw3.h>


namespace Fish
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());

	}

	Application::~Application()
	{


	}


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
			m_Window->OnUpdate();
		}
	}

}

