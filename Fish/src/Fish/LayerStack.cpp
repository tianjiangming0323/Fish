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
		//emplace ������ m_LayerInsert ������ָ���λ�ò�����Ԫ�� layer
		//��Ԫ�ػᱻ���뵽��ǰԪ�ص�ǰ��
		//emplace�ķ���ֵ��ָ���²���Ԫ�صĵ�����
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
	}

	//��vector
	//�ֱ����PushLayer(a),PushLayer(b),PushLayer(3),PushOverlay(A),PushOverlay(B),PushOverlay(C)
	//vector���Ϊ;        c,b,a,A,B,C
	//����cΪջ�ף�vectorͷ��
	//CΪջ����vector�ײ�


	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayerInsert--;
			//������ôд��ֻ��ɾջ�׼�c
			//c����룬��ַ��󣬹�ȷʵ��--

		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
			m_Layers.erase(it);
	}
}