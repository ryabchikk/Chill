#include <Chill.h>
#include "imgui/imgui.h"
class ExampleLayer : public Chill::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (Chill::Input::IsKeyPressed(CH_KEY_TAB))
			CH_TRACE("Tab key is pressed (poll)!");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(Chill::Event& event) override
	{
		if (event.GetEventType() == Chill::EventType::KeyPressed)
		{
			Chill::KeyPressedEvent& e = (Chill::KeyPressedEvent&)event;
			if (e.GetKeyCode() == CH_KEY_TAB)
				CH_TRACE("Tab key is pressed (event)!");
			CH_TRACE("{0}", (char)e.GetKeyCode());
		}
	}

};

class Sandbox : public Chill::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

Chill::Application* Chill::CreateApplication()
{
	return new Sandbox();
}