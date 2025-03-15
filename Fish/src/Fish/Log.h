#pragma once
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"
#include <memory>

namespace Fish
{
	class FISH_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger;  }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
		//inline �������� ��һ�֡����顱�������Ż������ĵ��÷�ʽ
		//ͨ������������Ϊinline�����������Գ��Խ������Ĵ���ֱ�Ӳ��뵽ÿ�����õ㣬������ͨ������ĺ���������ִ��
		//�������ڵĳ�Ա�������������ڶ��壬��Ĭ��Ϊinline���������ⶨ�壬����Ҫ��ʽ���inline
		//inline��������ͷ�ļ��У�����ͷ�ļ���ֱ��д��������
		//��Ҫ�Ը��Ӻ���ʹ��inline

		//static����̬��Ա��������ֻ�ܷ��ʾ�̬��Ա������CPP�ʼ� P7 32����

		//std::shared_ptr�� C++ ��׼�⣨STL���е�һ������ָ�����ͣ����� <memory> ͷ�ļ���
		//�������Զ�����̬������ڴ棬ͨ�����ü�������ʵ�ֶ��ָ�빲��ͬһ���ڴ������Ȩ���Ӷ������ڴ�й©
		//<>����ָ��ָ������ݵ��������ͣ�int��float�ȣ�

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
		//��̬��Ա���������ж�����ͬһ�����ݣ�CPP�ʼ� P7 32����
		// ����׶η����ڴ�
		// ���������������ʼ��
		//���綨��������Log��ʵ����log1��log2����ô���ǵĸñ�������ͬһ�ڴ�

	};

}


//Core Log Macros
#define FISH_CORE_TRACE(...)		::Fish::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define FISH_CORE_INFO(...)			::Fish::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FISH_CORE_WARN(...)			::Fish::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FISH_CORE_ERROR(...)		::Fish::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FISH_CORE_FATAL(...)		::Fish::Log::GetCoreLogger()->fatal(__VA_ARGS__)


//Core Log Macros
#define FISH_TRACE(...)				::Fish::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FISH_INFO(...)				::Fish::Log::GetClientLogger()->info(__VA_ARGS__)
#define FISH_WARN(...)				::Fish::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FISH_ERROR(...)				::Fish::Log::GetClientLogger()->error(__VA_ARGS__)
#define FISH_FATAL(...)				::Fish::Log::GetClientLogger()->fatal(__VA_ARGS__)

//����__VA_ARGS__Ϊ�ɱ�����꣬�������������������͵Ĳ���
//����������ð�� :: ��������ǰ��ʱ����ʾ��ȫ�������ռ䣨Global Namespace����ʼ����������
