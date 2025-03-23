#include "fishpch.h"
#include "WindowsInput.h"
#include "Fish/Application.h"
#include <GLFW/glfw3.h>

namespace Fish
{
	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		//��ȡGLFW���ڶ���
		//Application�����࣬ͨ��Get()���Application
		//����GetWindow()���Window�����
		//�ٵ���GetNativeWindow()���GLFWwindow*
		//���GLFWwindow* ָ��ǿ��ת��ΪGLFW�Ĵ������ͣ��Ա����GLFW API

		//static_cast<GLFWwindow*> �� C++ �е� ��ʽ����ת�������ڽ�һ��ָ������ת��Ϊ��һ�� ��ȷ��� ��ָ�����ͣ����罫 void* ת��Ϊ GLFWwindow*��
		//��ȻGetNativeWindow()���صľ���GLFWwindow*�����˴���������ת����Ŀ����Ϊ�����β�ͬƽ̨��ʵ�ֲ���
		//����ƽ̨���ܷ��ص���void*����
		auto state = glfwGetKey(window, keycode);
		//GLFW �ṩ�ĺ��������ڲ�ѯָ�������ĵ�ǰ״̬
		return state == GLFW_PRESS || state == GLFW_REPEAT;
		//ͨ�� GLFW �� ���ָ�������Ƿ��ڻ״̬�����»��ظ���������Ϸ��ͼ��Ӧ���д����������ĳ���ʵ�ַ�ʽ
	}


	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;

	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}


	float WindowsInput::GetMouseXImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		//ͨ���ṹ���� auto [x, y]��������󱻽⹹Ϊ���������ı��� x �� y
		return x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return y;
	}
}