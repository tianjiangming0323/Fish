#pragma once

#include "Fish/Core.h"

namespace Fish
{
	//events in Fish are currently blocking meaning when an event occurs,
	//it immediately gets dispatched and must be dealt with right then an there.
	//for the future a better strategy might be to buffer events in an event bus 
	//and process them during the event part of the update stage


	enum class EventType    //ö��ֵ����ͨ��EventType::����
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
	//BIT(n) ͨ��������Ϊһ���꣬��������һ�����������루bitmask�������ĺ����߼��� ������ 1 ���� n λ���Ӷ��ڶ������д���һ��ֻ�е� n λΪ 1������λΪ 0 ����ֵ��
	//�����������һ���¼����ڶ����𣬼����¼�ͬʱ����Input��Keyboard



#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

	//C++�ĺ궨��Ĭ���ǵ��еģ��Ի��з���������
	//�������������������Ҫд�ɶ��У�������������䣩�������� \ ���ӡ�
	//## ����������Ʒ�  EVENT_CLASS_TYPE(KeyPressed) -----------    EventTYpe::KeyPressed
	//# ����ַ���ת����������typeת��Ϊ�ַ���

	//override ��ʽ�������ǻ�����麯�������������鸲���Ƿ�Ϸ���
	//����Ҫ���ǻ���� �����麯�� ʱ������ͬʱʹ�� const �� override��

	//���ж����ǰ������������ֵ������ͬ������������
	//static �����ڱ��������ã��ṩ����ʵ���������ͷ���
	//virtual �麯��ʵ������ʱ��̬
	//��CPP�ʼ�P12 45�� ��̬��ʵ��������Ϊ������ַ�����н׶βŰ�

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class FISH_API Event
	{
		friend class EventDispatcher;
		//��Ԫ  CPP�ʼ�P9 37��
		//EventDispatcher ���Է��� Event�е�˽�г�Ա

	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;   //��λ������
		}
	protected:
		bool m_Handled = false;
		//if an event was handled
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;        //�¼�����������
		//std::function ��ģ�������һ���������ͣ�boolΪ����ֵ���ͣ�T&Ϊ���������б�
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{

		}

		template<typename T>
		bool Dispatch(EventFn<T> func)   //������std::function,func���Կ���һ�������������ֿ��Կ���һ������
		{
			if (m_Event.GetEventType() == T::GetStaticType())     //����ƥ����
			{
				m_Event.m_Handled = func(*(T*)&m_Event);              //��ȫת������ô�����
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;      //��ǰ���ַ����¼�����

	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}



}

