#include "GameLayer.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace Chill;

GameLayer::GameLayer(): Layer("GameLayer")
{
	auto& window = Application::Get().GetWindow();
	
	CreateCamera(window.GetWidth(), window.GetHeight());

	Random::Init();
}

void GameLayer::Attach()
{
	level.Init();

	ImGuiIO io = ImGui::GetIO();
	font = io.Fonts->AddFontFromFileTTF("assets/EightBits.ttf", 120.0f);
}

void GameLayer::Detach()
{
}

void GameLayer::Update(Chill::Timestep ts)
{
	time += ts;
	if ((int)(time * 10.0f) % 8 > 4)
		blink = !blink;

	if (level.IsGameOver()) {
		status = StatusGame::GameOver;
	}
		

	const auto& playerPosition = level.GetPlayer().GetPosition();

	mainCamera->SetPosition({ playerPosition.x, playerPosition.y, 0.0f });

	switch (status)
	{
		case StatusGame::Play:
		{
			level.OnUpdate(ts);
			break;
		}
	}

	Chill::RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1 });
	Chill::RenderCommand::Clear();

	Chill::Renderer2D::BeginScene(*mainCamera);

	level.Render();
	
	Chill::Renderer2D::EndScene();
}

void GameLayer::OnImGuiRender() 
{
	
	const auto& window = Application::Get().GetWindow();
	const auto windowPos = ImGui::GetWindowPos();
	const auto centerTextX = window.GetWidth() * 0.5f - 600.0f;
	const auto centerTextGameOverX = window.GetWidth() * 0.5f - 200.0f;

	switch (status) {
	case StatusGame::Play:

		RenderPlayerScore(windowPos);
		break;

	case StatusGame::MainMenu:
		
		if (blink) {
			RenderCenteredText("Press left mouse button to play", 120.0f, { windowPos.x + centerTextX, windowPos.y + 50.0f });
		}

		break;

	case StatusGame::GameOver:

		if (blink) {
			RenderCenteredText("Game over", 120.0f, { windowPos.x + centerTextGameOverX, windowPos.y + 50.0f });
		}
		
		RenderPlayerScore({ windowPos.x + centerTextGameOverX + 100.0f, windowPos.y + 200.0f });
		
		break;
	}
}

void GameLayer::RenderPlayerScore(const ImVec2& position) 
{
	const uint32_t score = level.GetPlayer().GetScore();
	const std::string scoreText = "Score " + std::to_string(score);

	RenderCenteredText(scoreText, 48.0f, position);
}

void GameLayer::RenderCenteredText(const std::string& text, float fontSize, const ImVec2& position)
{
	ImGui::GetForegroundDrawList()->AddText(font, fontSize, position, 0xffffffff, text.c_str());
}

void GameLayer::OnEvent(Chill::Event& e)
{
	EventDispatcher dispatcher(e);
	
	dispatcher.Dispatch<WindowResizeEvent>(CH_BIND_EVENT_FN(GameLayer::ResizeWindow));
	dispatcher.Dispatch<MouseButtonPressedEvent>(CH_BIND_EVENT_FN(GameLayer::OnMouseButtonPressed));
}

bool GameLayer::OnMouseButtonPressed(Chill::MouseButtonPressedEvent& e)
{
	if (status == StatusGame::GameOver) {
		level.Reset();
	}
		
	status = StatusGame::Play;
	
	return false;
}

bool GameLayer::ResizeWindow(Chill::WindowResizeEvent& e)
{
	CreateCamera(e.GetWidth(), e.GetHeight());

	return false;
}

void GameLayer::CreateCamera(uint32_t width, uint32_t height)
{
	float aspectRatio = (float)width / (float)height;

	float camWidth = 8.0f;
	float bottom = -camWidth;
	float top = camWidth;
	float left = bottom * aspectRatio;
	float right = top *aspectRatio;

	mainCamera = CreateScope<OrthographicCamera>(left, right, bottom, top);
}
