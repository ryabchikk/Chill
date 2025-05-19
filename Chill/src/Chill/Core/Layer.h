#pragma once

#include "Chill/Core/Core.h"
#include "Chill/Core/Timestep.h"
#include "Chill/Events/Event.h"

namespace Chill {

	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		
		virtual ~Layer() = default;

		virtual void Attach() {}
		virtual void Detach() {}
		virtual void Update(Timestep ts) {}

		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	
	protected:
		std::string m_DebugName;
	};

}