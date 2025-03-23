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
		//获取GLFW窗口对象
		//Application单例类，通过Get()获得Application
		//调用GetWindow()获得Window类对象
		//再调用GetNativeWindow()获得GLFWwindow*
		//最后将GLFWwindow* 指针强行转换为GLFW的窗口类型，以便调用GLFW API

		//static_cast<GLFWwindow*> 是 C++ 中的 显式类型转换，用于将一个指针类型转换为另一个 明确相关 的指针类型（例如将 void* 转换为 GLFWwindow*）
		//虽然GetNativeWindow()返回的就是GLFWwindow*，但此处调用类型转换的目的是为了屏蔽不同平台的实现差异
		//其他平台可能返回的是void*类型
		auto state = glfwGetKey(window, keycode);
		//GLFW 提供的函数，用于查询指定按键的当前状态
		return state == GLFW_PRESS || state == GLFW_REPEAT;
		//通过 GLFW 库 检测指定按键是否处于活动状态（按下或重复），是游戏或图形应用中处理键盘输入的常见实现方式
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
		//通过结构化绑定 auto [x, y]，这个对象被解构为两个单独的变量 x 和 y
		return x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return y;
	}
}