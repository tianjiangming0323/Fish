#pragma once

#ifdef FISH_PLATFORM_WINDOWS

extern Fish::Application* Fish::CreateApplication();
//�ؼ��� extern ��ʾ�ú����Ķ�������һ�����뵥Ԫ���� .cpp �ļ����У���ǰ�ļ�ֻ���������Ĵ��ڣ����߱��������Ժ�����ʱ���ҵ�����ʵ�֡���

int main(int argc, char** argv)
//��������main�������Խ��������в���
//ǰ��Ϊ����������Argument Count������ʾ�����в�����������������������������
//����Ϊ����ֵ���飨Argument Values�����洢���������в������ַ���ָ�����顣	
{
	auto app = Fish::CreateApplication();
	app->run();
	delete app;

}



#endif