#include <Fish.h>

class Sandbox : public Fish::Application
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
