#include "chpch.h"
#include "Chill/Core/Application.h"
#include "Chill/Core/Log.h"
#include "Chill/Renderer/Renderer.h"
#include "Chill/Core/Input.h"
#include <glfw/glfw3.h>

namespace Chill {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		CH_PROFILE_FUNCTION();
		CH_CORE_ASSERT(!s_Instance, "Application already exists!");
		
		InitializeApplication();
	}
	
	void Application::InitializeApplication() 
	{
		s_Instance = this;

		CreateMainWindow();
		InitializeGraphics();
		SetupDebugUI();
	}

	void Application::CreateMainWindow() 
	{
		window = Window::Create();
		window->SetEventCallback(CH_BIND_EVENT_FN(Application::OnEvent));
	}

	void Application::SetupDebugUI() 
	{
		imGuiLayer = new ImGuiLayer();
		AddOverlay(imGuiLayer);
	}

	void Application::InitializeGraphics() 
	{
		Renderer::Initialize();
	}

	Application::~Application()
	{
		CH_PROFILE_FUNCTION();
		Renderer::Shutdown();
	}

	void Application::AddLayer(Layer* layer)
	{
		CH_PROFILE_FUNCTION();
		m_LayerStack.AddLayer(layer);
		layer->Attach();
	}

	void Application::AddOverlay(Layer* layer)
	{
		CH_PROFILE_FUNCTION();
		m_LayerStack.AddOverlay(layer);
		layer->Attach();
	}

	void Application::OnEvent(Event& e)
	{
		CH_PROFILE_FUNCTION();
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(CH_BIND_EVENT_FN(Application::CloseWindow));
		dispatcher.Dispatch<WindowResizeEvent>(CH_BIND_EVENT_FN(Application::ResizeWindow));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		CH_PROFILE_FUNCTION();
		
		while (running)
		{
			CH_PROFILE_SCOPE("RunLoop");

			float time = (float)glfwGetTime();
			
			Timestep timestep = time - m_LastFrameTime;
			
			m_LastFrameTime = time;

			if (!minimized) {
				UpdateLayers(timestep);
				RenderInterface();
			}

			window->Update();
		}
	}

	void Application::UpdateLayers(Timestep timestep) 
	{
		CH_PROFILE_SCOPE("Layer Updates");
		
		for (Layer* layer : m_LayerStack) 
		{
			layer->Update(timestep);
		}
	}

	void Application::RenderInterface()
	{
		if (minimized) {
			return;
		} 

		imGuiLayer->Begin();
		{
			CH_PROFILE_SCOPE("ImGui Rendering");

			for (Layer* layer: m_LayerStack) 
			{
				layer->OnImGuiRender();
			}
		}

		imGuiLayer->End();
	}

	bool Application::CloseWindow(WindowCloseEvent& e)
	{
		running = false;
		return true;
	}

	bool Application::ResizeWindow(WindowResizeEvent& e)
	{
		CH_PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetHeight() == 0) {
			minimized = true;
			return false;
		}

		minimized = false;

		Renderer::ResizeWindow(e.GetWidth(), e.GetHeight());

		return false;
	}

}