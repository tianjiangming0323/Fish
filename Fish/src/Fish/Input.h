#pragma once

#include "Fish/Core.h"

namespace Fish
{
	class FISH_API Input
	{
	public:
		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }


	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;


	private:
		static Input* s_Instance;

	};
}

//polling（轮询） 是一种 主动查询状态或数据 的编程模式，其核心思想是 通过循环或定时检查某个条件是否满足，而不是等待事件主动通知（如回调函数或事件驱动）
//轮询不会阻塞当前线程，但可能占用 CPU 资源（如果轮询频率过高）
//优点：实时性要求高
//缺点：消耗CPU资源，不适合处理高并发情景
