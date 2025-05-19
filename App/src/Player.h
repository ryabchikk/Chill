#pragma once

#include <Chill.h>

#include "Random.h"

class Player
{
	public:
		Player();

		void LoadAssets();

		void OnUpdate(Chill::Timestep ts);
		void Render();

		void Reset();

		float GetRotation() { return velocity.y * 4.0f - 90.0f; }
		const glm::vec2& GetPosition() const { return position; }

		uint32_t GetScore() const { return (uint32_t)(position.x + 10.0f) / 10.0f; }

	private:
		glm::vec2 position = { -10.0f, 0.0f };
		glm::vec2 velocity = { 5.0f, 0.0f };

		float power = 0.5f;
		float gravity = 0.4f;
		float time = 0.0f;

		Chill::Ref<Chill::Texture2D> playerTexture;
};