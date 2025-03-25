#pragma once

#include "Fish/Core.h"
#include "Layer.h"
#include <vector>

namespace Fish
{
	class FISH_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		//��Ӳ�
		//��ͨ�㣨Layer����ͨ��������Ϸ/Ӧ�õ����߼����糡������ɫ����
		//���ǲ㣨Overlay����ͨ������ UI Ԫ�أ���˵���HUD����ʼ����ʾ����ͨ���Ϸ���
		//���𣺸��ǲ�ᱻ���뵽 m_Layers ��ĩβ������ͨ����뵽�м䣨�����߼������ģ���

		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);
		//�Ƴ���

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		//begin()���������m_Layers����ʼ��������ָ�������е�һ��Ԫ��
		
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
		//end()���������m_Layers�Ľ�����������ָ�����������һ��Ԫ�ص���һ��λ��

	private:
		std::vector<Layer*> m_Layers;          // �洢���в������
		//std::vector<Layer*>::iterator m_LayerInsert;   // ��¼��ͨ��Ĳ���λ�ã����������Կ���һ��ָ��
		unsigned int m_LayerInsertIndex = 0;
	};
}

