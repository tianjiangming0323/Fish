#pragma once

#include "Fish/Core.h"

namespace Fish
{
	//events in Fish are currently blocking meaning when an event occurs,
	//it immediately gets dispatched and must be dealt with right then an there.
	//for the future a better strategy might be to buffer events in an event bus 
	//and process them during the event part of the update stage


	enum class EventType    //枚举值必须通过EventType::访问
	{
		None = 0,
		WindowClose, WindowResize, WindowFoucus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		//ApplicationEvent.h
		KeyPressed, KeyReleased,
		//KeyEvent.h
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
		//MouseEvent.h

	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),    //0b0001
		EventCategoryInput = BIT(1),          //0b0010      (2)
		EventCategoryKeyboard = BIT(2),       //0b0100      (4)
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};
	//BIT was defined in Core.h
	//BIT(n) 通常被定义为一个宏，用于生成一个二进制掩码（bitmask）。它的核心逻辑是 将数字 1 左移 n 位，从而在二进制中创建一个只有第 n 位为 1，其他位为 0 的数值。
	//分类设计允许一个事件属于多个类别，键盘事件同时属于Input和Keyboard



#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

	//C++的宏定义默认是单行的（以换行符结束）。
	//多行需求：如果宏内容需要写成多行（比如包含多个语句），必须用 \ 连接。
	//## 宏的连接令牌符  EVENT_CLASS_TYPE(KeyPressed) -----------    EventTYpe::KeyPressed
	//# 宏的字符串转化符，参数type转化为字符串

	//override 显式声明覆盖基类的虚函数，编译器会检查覆盖是否合法。
	//当需要覆盖基类的 常量虚函数 时，必须同时使用 const 和 override。

	//宏中定义的前两个函数返回值类型相同，但不是冗余
	//static 函数在编译器调用，提供无需实例化的类型访问
	//virtual 虚函数实现运行时多态
	//见CPP笔记P12 45条 多态的实现正是因为函数地址在运行阶段才绑定

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class FISH_API Event
	{
		friend class EventDispatcher;
		//友元  CPP笔记P9 37条
		//EventDispatcher 可以访问 Event中的私有成员

	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;   //按位与运算
		}
	protected:
		bool m_Handled = false;
		//if an event was handled
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;        //事件处理函数别名
		//std::function 的模板参数是一个函数类型，bool为返回值类型，T&为函数参数列表
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{

		}

		template<typename T>
		bool Dispatch(EventFn<T> func)   //得益于std::function,func可以看做一个参数，但它又可以看成一个函数
		{
			if (m_Event.GetEventType() == T::GetStaticType())     //类型匹配检查
			{
				m_Event.m_Handled = func(*(T*)&m_Event);              //安全转换后调用处理函数
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;      //当前被分发的事件引用

	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}



}

