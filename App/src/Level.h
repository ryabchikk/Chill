#pragma once

#include "Player.h"

struct Pillar
{
	glm::vec3 TopPosition = { 0.0f, 10.0f, 0.0f };
	glm::vec2 TopScale = { 15.0f, 20.0f };

	glm::vec3 BottomPosition = { 10.0f, 10.0f, 0.0f};
	glm::vec2 BottomScale = { 15.0f, 20.0f };
};

class Level
{
	public:
		void Init();
		void OnUpdate(Chill::Timestep ts);
		void Render();
		void Reset();
		
		bool IsGameOver() const { return gameOverFlag; }

		Player& GetPlayer() { return player; }

	private:
		void CreatePillar(int index, float offset);
		
		bool CollisionTest();

		void GameOver();
	
	private:
		Player player;

		bool gameOverFlag = false;

		float pillarTarget = 30.0f;
		
		int pillarIndex = 0;

		glm::vec3 pillarHSV = { 0.0f, 0.8f, 0.8f };

		std::vector<Pillar> pillars;

		Chill::Ref<Chill::Texture2D> triangleTexture;
};