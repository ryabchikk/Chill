#pragma once
#include "Core.h"

namespace Chill {

	class CHILL_API Application
	{
	public:
		Application();
		virtual~Application();

		void Run();
	};

	Application* CreateApplication();
}
