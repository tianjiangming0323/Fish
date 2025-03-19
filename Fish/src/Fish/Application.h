#pragma once

#include "Core.h"

#include "Events/Event.h"
#include "Fish/Events/ApplicationEvent.h"
#include "Window.h"


namespace Fish
{
	class FISH_API Application
	{

	public:
		Application();
		virtual ~Application();
		//��̬����Ϊ       ��̬��̬���������ء����������       ��       ��̬��̬����������麯��
		//��̬��̬:������ַ���    
		//������     1.�м̳й�ϵ    2.������д�����麯��   3.����ָ�������ָ���������
		//ԭ��vfptr��vftable
		// ���麯�� ������
		// 
		//����ָ����������ʱ�򲻻������������������������������ж������ԣ��޷��������ڴ�й¶
		//������������������ĳ�������
		//����������Ҫ��������Ҳ��Ҫ��ʵ��
		// ��Ϊ������������Թ����ڶ�������Ҫ�ͷ�
		// �봿�麯����ͬ�����麯��=0�������ˣ�����������Ҫ������ʵ��
		//���˴�������Ҳ���ڳ����� 
		//

		void run();

		void OnEvent(Event& e);
	private:

		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		//m_Windowӵ�жԴ��ڶ����Ψһ����Ȩ����m_Window������ʱ�����ڶ���Ҳ�ᱻ�Զ����٣��������ڹ�����Դ���������ڣ������ڴ�й©
		//unique_ptr ���ܱ����ƣ��������캯���͸�ֵ�������ɾ������������ͨ�� std::move �ƶ�����Ȩ��
		//�� m_Window �뿪�����������ڶ������٣�������ʽ���� reset() ʱ��unique_ptr ���Զ����� delete �ͷ���ָ��� Window ����
		bool m_Running = true;
	};

	//To be defined in the CLIENT
	Application* CreateApplication();

}
