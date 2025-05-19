#pragma once

#include "Chill/Core/Layer.h"

#include "Chill/Events/ApplicationEvent.h"
#include "Chill/Events/KeyEvent.h"
#include "Chill/Events/MouseEvent.h"

namespace Chill {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void Attach() override;
		virtual void Detach() override;

		void Begin();
		void End();
	private:
		float time = 0.0f;
	};

}


