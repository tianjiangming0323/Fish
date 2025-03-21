#include <Fish.h>

class ExampleLayer : public Fish::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

	}

	void OnUpdate() override
	{
		FISH_INFO("ExampleLayer::Update");
	}

	void OnEvent(Fish::Event& event) override
	{
		FISH_TRACE("{0}", event.ToString());
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
		PushOverlay(new Fish::ImGuiLayer());

	}

	~Sandbox()
	{

	}

};

Fish::Application* Fish::CreateApplication()
{

	return new Sandbox();
}
