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
		//添加层
		//普通层（Layer）：通常用于游戏/应用的主逻辑（如场景、角色）。
		//覆盖层（Overlay）：通常用于 UI 元素（如菜单、HUD），始终显示在普通层上方。
		//区别：覆盖层会被插入到 m_Layers 的末尾，而普通层插入到中间（具体逻辑见下文）。

		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);
		//移除层

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		//begin()函数，获得m_Layers的起始迭代器，指向容器中第一个元素
		
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
		//end()函数，获得m_Layers的结束迭代器，指向容器中最后一个元素的下一个位置

	private:
		std::vector<Layer*> m_Layers;          // 存储所有层的容器
		//std::vector<Layer*>::iterator m_LayerInsert;   // 记录普通层的插入位置，迭代器可以看做一个指针
		unsigned int m_LayerInsertIndex = 0;
	};
}

