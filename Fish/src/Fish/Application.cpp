//��ķ��ļ���д
//��ʹ��ʱֻ����ͷ�ļ�����
//cpp �ʼ� P5��25��
#include "Application.h"
#include "Fish/Events/ApplicationEvent.h"
#include "Fish/Log.h"


namespace Fish
{
	Application::Application()
	{


	}

	Application::~Application()
	{


	}


	void Application::run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			FISH_TRACE(e.ToString());
		}

		if (e.IsInCategory(EventCategoryInput))
		{
			FISH_TRACE(e.ToString());
		}
		while (true);
	}

}

