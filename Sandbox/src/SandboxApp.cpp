#include <Fish.h>

class Sandbox : public Fish::Application
//Fish::Application在Core.h中通过FISH_BUILD_DLL赋值
//而在子类中，这个“符号导出”不会被继承
{
public:
	Sandbox()
	{


	}

	~Sandbox()
	{

	}

};

Fish::Application* Fish::CreateApplication()
{

	return new Sandbox();
}
