#include <Fish.h>

class Sandbox : public Fish::Application
//Fish::Application��Core.h��ͨ��FISH_BUILD_DLL��ֵ
//���������У���������ŵ��������ᱻ�̳�
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
