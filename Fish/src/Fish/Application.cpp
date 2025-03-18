//类的分文件编写
//在使用时只包含头文件即可
//cpp 笔记 P5第25条
#include "fishpch.h"    
//每个cpp文件中都需要包含预编译头文件，且需要第一个包含
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
			//设置清除颜色缓冲时使用的颜色
			glClear(GL_COLOR_BUFFER_BIT);
			//清除当前帧缓冲区的指定部分（这里是颜色缓冲区）
			//GL_DEPTH_BUFFER_BIT：清除深度缓冲区（用于3D深度测试）。
			//GL_STENCIL_BUFFER_BIT：清除模板缓冲区（用于模板测试）。
			m_Window->OnUpdate();
		}
	}

}

