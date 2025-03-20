#include "fishpch.h"
#include "LayerStack.h"

namespace Fish
{
	LayerStack::LayerStack()
	{
		m_LayerInsert = m_Layers.begin();
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
		//emplace 方法在 m_LayerInsert 迭代器指向的位置插入新元素 layer
		//新元素会被插入到当前元素的前面
		//emplace的返回值是指向新插入元素的迭代器
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
	}

	//空vector
	//分别调用PushLayer(a),PushLayer(b),PushLayer(3),PushOverlay(A),PushOverlay(B),PushOverlay(C)
	//vector结果为;        c,b,a,A,B,C
	//其中c为栈底，vector头部
	//C为栈顶，vector底部


	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayerInsert--;
			//代码这么写，只能删栈底即c
			//c最后传入，地址最大，故确实是--

		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
			m_Layers.erase(it);
	}
}