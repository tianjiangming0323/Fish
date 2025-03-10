#pragma once

#include "Core.h"

namespace Fish
{
	class FISH_API Application
	{

	public:
		Application();
		virtual ~Application();

		void run();
	};

	//To be defined in the CLIENT
	Application* CreateApplication();

}
