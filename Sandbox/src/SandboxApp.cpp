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
			//静态类，不用生成类对象就可以直接调用函数
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
			//类型转换，将Event父类转换成KeyEvent子类
			if (e.GetKeyCode() == FISH_KEY_TAB)
				FISH_TRACE("Tab key is pressed(event)!");
			FISH_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox : public Fish::Application
//Fish::Application在Core.h中通过FISH_BUILD_DLL赋值
//而在子类中，这个“符号导出”不会被继承
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
