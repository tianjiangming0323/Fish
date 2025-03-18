#include "fishpch.h"
#include "Log.h"

namespace Fish
{
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		//%^:start color range (can be used only once)
		//%T:ISO 8601 time format (HH:MM:SS)
		//%n:Logger's name
		//%v:The actual text to log
		//%$:end color range
		//https://github.com/gabime/spdlog/wiki/3.-Custom-formatting

		s_CoreLogger = spdlog::stdout_color_mt("Fish");
		//����һ����ΪFish��console
		s_CoreLogger->set_level(spdlog::level::trace);
		//������־����Ϊ trace����ʾ��¼���м������־
		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);

	}
}
