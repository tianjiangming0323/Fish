#pragma once

#include "Core.h"

#include "Window.h"
#include "Fish/LayerStack.h"
#include "Fish/Events/Event.h"
#include "Fish/Events/ApplicationEvent.h"

#include "Fish/ImGui/ImGuiLayer.h"


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
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
		//s_InstanceΪ��ָ�룬���ؽ�����
		
	private:

		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		//m_Windowӵ�жԴ��ڶ����Ψһ����Ȩ����m_Window������ʱ�����ڶ���Ҳ�ᱻ�Զ����٣��������ڹ�����Դ���������ڣ������ڴ�й©
		//unique_ptr ���ܱ����ƣ��������캯���͸�ֵ�������ɾ������������ͨ�� std::move �ƶ�����Ȩ��
		//�� m_Window �뿪�����������ڶ������٣�������ʽ���� reset() ʱ��unique_ptr ���Զ����� delete �ͷ���ָ��� Window ����

		

		ImGuiLayer* m_ImGuiLayer;

		bool m_Running = true;
		LayerStack m_LayerStack;

	private:
		static Application* s_Instance;
		//Application�����ó��˵�����
		//ȷ��һ����ֻ��һ��ʵ�������ṩһ��ȫ�ַ��ʵ㣬�������������ȡ��ʵ�����������ڹ���ȫ����Դ�������á����ݿ����ӡ���־ϵͳ�ȣ�
		//��Ȼ�����й��캯����public
		//�����Խ����캯��private�������ͽ�ֹ������new�ȹؼ��ֽ����ⲿʵ����
		//��������Ҫ�����������ݽ�����ֻ��ͨ����̬����Get()ʵ��
	};

	//To be defined in the CLIENT
	Application* CreateApplication();

}
