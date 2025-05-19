#pragma once

#include "Chill.h"

#include "Level.h"
#include <imgui/imgui.h>

class GameLayer : public Chill::Layer
{
public:
	GameLayer();
	virtual ~GameLayer() = default;

	virtual void Attach() override;
	virtual void Detach() override;

	void Update(Chill::Timestep ts) override;
	
	virtual void RenderPlayerScore(const ImVec2& position);
	virtual void RenderCenteredText(const std::string& text, float fontSize, const ImVec2& position);
	virtual void OnImGuiRender() override;

	void OnEvent(Chill::Event& e) override;
	
	bool OnMouseButtonPressed(Chill::MouseButtonPressedEvent& e);
	bool ResizeWindow(Chill::WindowResizeEvent& e);

private:
	void CreateCamera(uint32_t width, uint32_t height);

private:
	Chill::Scope<Chill::OrthographicCamera> mainCamera;

	Level level;
	ImFont* font;
	
	float time = 0.0f;
	
	bool blink = false;

	enum class StatusGame
	{
		Play = 0, MainMenu = 1, GameOver = 2
	};

	StatusGame status = StatusGame::MainMenu;
};