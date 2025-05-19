#pragma once

#include "Chill/Core/Core.h"

#include "Chill/Core/Window.h"
#include "Chill/Core/LayerStack.h"
#include "Chill/Events/Event.h"
#include "Chill/Events/ApplicationEvent.h"

#include "Chill/Core/Timestep.h"

#include "Chill/ImGui/ImGuiLayer.h"

namespace Chill 
{

	class Application
	{
		public:
			Application();
			virtual ~Application();

			void Run();
			void OnEvent(Event& e);
			void AddLayer(Layer* layer);
			void AddOverlay(Layer* layer);

			inline Window& GetWindow() { return *window; }
			inline static Application& Get() { return *s_Instance; }
	
		private:
			bool CloseWindow(WindowCloseEvent& e);
			bool ResizeWindow(WindowResizeEvent& e);

		private:
			std::unique_ptr<Window> window;
		
			ImGuiLayer* imGuiLayer;

			bool running = true;
			bool minimized = false;
		
			LayerStack m_LayerStack;
		
			float m_LastFrameTime = 0.0f;
	
		private:
			static Application* s_Instance;
	
		private:
			void InitializeApplication();
			void CreateMainWindow();
			void SetupDebugUI();
			void InitializeGraphics();
			void UpdateLayers(Timestep timestep);
			void RenderInterface();
	};

	Application* CreateApplication();

}