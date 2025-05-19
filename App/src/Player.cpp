#include "Player.h"

#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>

using namespace Chill;

Player::Player(){}

void Player::LoadAssets()
{
	playerTexture = Texture2D::Create("assets/textures/player_texture.png");
}

void Player::OnUpdate(Chill::Timestep ts)
{
	time += ts;

	if (Input::IsKeyPressed(CH_KEY_SPACE)) {
		velocity.y += power;
	}
	else {
		velocity.y -= gravity;
	}

	position += velocity * (float)ts;
}

void Player::Render()
{
	Renderer2D::DrawQuad({ position.x, position.y, 0.5f }, { 1.0f, 1.0f }, 0.0f, playerTexture);
}

void Player::Reset()
{
	position = { -10.0f, 0.0f };
	velocity = { 5.0f, 0.0f };
}
