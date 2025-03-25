#include <Fish.h>

#include "imgui/imgui.h"

class ExampleLayer : public Fish::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

	}


	void OnUpdate() override
	{
		//FISH_INFO("ExampleLayer::Update");
		if (Fish::Input::IsKeyPressed(FISH_KEY_TAB))
			//��̬�࣬�������������Ϳ���ֱ�ӵ��ú���
			FISH_TRACE("Tab key is pressed(poll)!");
	}


	virtual void OnImGuiRender() override
	{
		/*ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();*/
	}

	void OnEvent(Fish::Event& event) override
	{
		//FISH_TRACE("{0}", event.ToString());
		if (event.GetEventType() == Fish::EventType::KeyPressed)
		{
			Fish::KeyPressedEvent& e = (Fish::KeyPressedEvent&)event;
			//����ת������Event����ת����KeyEvent����
			if (e.GetKeyCode() == FISH_KEY_TAB)
				FISH_TRACE("Tab key is pressed(event)!");
			FISH_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox : public Fish::Application
//Fish::Application��Core.h��ͨ��FISH_BUILD_DLL��ֵ
//���������У���������ŵ��������ᱻ�̳�
{
public:
	Sandbox()
	{ 
		PushLayer(new ExampleLayer());
		//PushOverlay(new Fish::ImGuiLayer());

	}

	~Sandbox()
	{

	}

};

Fish::Application* Fish::CreateApplication()
{

	return new Sandbox();
}
