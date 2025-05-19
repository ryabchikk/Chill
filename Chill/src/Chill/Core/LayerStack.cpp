#include "chpch.h"
#include "Chill/Core/LayerStack.h"

namespace Chill {

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
		{
			layer->Detach();
			delete layer;
		}
	}

	void LayerStack::AddLayer(Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
	}

	void LayerStack::AddOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, layer);
		if (it != m_Layers.begin() + m_LayerInsertIndex)
		{
			layer->Detach();
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), overlay);
		if (it != m_Layers.end())
		{
			overlay->Detach();
			m_Layers.erase(it);
		}
	}

}