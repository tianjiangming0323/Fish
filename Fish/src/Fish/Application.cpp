//类的分文件编写
//在使用时只包含头文件即可
//cpp 笔记 P5第25条
#include "fishpch.h"    
//每个cpp文件中都需要包含预编译头文件，且需要第一个包含
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

