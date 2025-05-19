#pragma once

#include "Core.h"
#include "Chill/Core/Layer.h"

#include <vector>

namespace Chill {

	class LayerStack
	{
	public:
		LayerStack() = default;
		~LayerStack();

		void AddLayer(Layer* layer);
		void AddOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex = 0;
	};

}