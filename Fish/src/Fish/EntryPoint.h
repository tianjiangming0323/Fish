#pragma once

#ifdef FISH_PLATFORM_WINDOWS

extern Fish::Application* Fish::CreateApplication();
//�ؼ��� extern ��ʾ�ú����Ķ�������һ�����뵥Ԫ���� .cpp �ļ����У���ǰ�ļ�ֻ���������Ĵ��ڣ����߱��������Ժ�����ʱ���ҵ�����ʵ�֡���

//��ʵ�Լ�������һ���ɻ��Լ���ʱ�Ѿ���������������Ļ������õĿ�ܣ����д��붼��SandboxApp������
//��Ϊʲô��Ҫдһ������
//�Ƚϴֱ���Ŀǰ��⣺���ÿ������ɰѱ����õ���δ���ԭ�ⲻ��д������λ��
//��Ȼ��ˣ���ô��SandboxApp.cpp�У�main������λ����ʵ��CreateApplication���������棬����Ҫ����һ��



int main(int argc, char** argv)
//��������main�������Խ��������в���
//ǰ��Ϊ����������Argument Count������ʾ�����в�����������������������������
//����Ϊ����ֵ���飨Argument Values�����洢���������в������ַ���ָ�����顣	
{
	Fish::Log::Init();
	//InitΪ��̬��Ա�������ʿ��Բ�ʵ�����ֱ࣬����������
	//CPP�ʼ� P7 32��
	FISH_CORE_WARN("Initialized Log!");
	int a = 5;
	FISH_INFO("Hello!  var = {0}",a);

	auto app = Fish::CreateApplication();
	app->run();
	delete app;

}



#endif