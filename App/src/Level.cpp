#include "Level.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace Chill;

static glm::vec4 HSVtoRGB(const glm::vec3& hsv) 
{
	const float hue_angle = hsv.x * 360.0f;
	const float saturation = hsv.y;
	const float value = hsv.z;

	const float chroma = saturation * value;
	const float hue_sector = fmod(hue_angle / 60.0f, 2.0f);
	const float intermediate = chroma * (1.0f - fabs(hue_sector - 1.0f));
	const float margin = value - chroma;

	float red, green, blue;

	switch (static_cast<int>(hue_angle) / 60) 
	{
		case 0:  red = chroma; green = intermediate; blue = 0.0f;
			break;
		case 1:  red = intermediate; green = chroma; blue = 0.0f;
			break;
		case 2:  red = 0.0f; green = chroma; blue = intermediate;
			break;
		case 3:  red = 0.0f; green = intermediate; blue = chroma;
			break;
		case 4:  red = intermediate; green = 0.0f; blue = chroma;
			break;
		default: red = chroma; green = 0.0f; blue = intermediate;
			break;
	}

	return glm::vec4(red + margin, green + margin, blue + margin, 1.0f);
}

static bool PointInTriangle(const glm::vec2& point, const glm::vec2& a, const glm::vec2& b, const glm::vec2& c) 
{
	const float bary_s = a.y * c.x - a.x * c.y + (c.y - a.y) * point.x + (a.x - c.x) * point.y;
	
	const float bary_t = a.x * b.y - a.y * b.x + (a.y - b.y) * point.x + (b.x - a.x) * point.y;

	if ((bary_s < 0) != (bary_t < 0)) {
		return false;
	}

	const float triangle_area = -b.y * c.x + a.y * (c.x - b.x) + a.x * (b.y - c.y) + b.x * c.y;

	if (triangle_area < 0) {
		return bary_s <= 0 && (bary_s + bary_t) >= triangle_area;
	}
	else {
		return bary_s >= 0 && (bary_s + bary_t) <= triangle_area;
	}
}


void Level::Init()
{
	triangleTexture = Texture2D::Create("assets/textures/Triangle.png");
	player.LoadAssets();

	pillars.resize(5);

	for (int i = 0; i < 5; i++) 
	{
		CreatePillar(i, i * 10.0f);
	}	
}

void Level::OnUpdate(Chill::Timestep ts)
{
	player.OnUpdate(ts);

	if (CollisionTest())
	{
		GameOver();
		return;
	}

	pillarHSV.x += 0.1f * ts;
	if (pillarHSV.x > 1.0f)
		pillarHSV.x = 0.0f;

	if (player.GetPosition().x > pillarTarget)
	{
		CreatePillar(pillarIndex, pillarTarget + 20.0f);
		pillarIndex = ++pillarIndex % pillars.size();
		pillarTarget += 10.0f;
	}
}

void Level::Render()
{
	const auto& playerPos = player.GetPosition();

	glm::vec4 color = HSVtoRGB(pillarHSV);

	Renderer2D::DrawQuad({ playerPos.x, 0.0f, -0.8f }, { 50.0f, 50.0f }, { 0.3f, 0.3f, 0.3f, 1.0f });

	Renderer2D::DrawQuad({ playerPos.x,  34.0f }, { 50.0f, 50.0f }, color);
	Renderer2D::DrawQuad({ playerPos.x, -34.0f }, { 50.0f, 50.0f }, color);

	for (auto& pillar : pillars)
	{
		Renderer2D::DrawQuad(pillar.TopPosition, pillar.TopScale, glm::radians(180.0f), triangleTexture, color);
		Renderer2D::DrawQuad(pillar.BottomPosition, pillar.BottomScale, 0.0f, triangleTexture, color);
	}

	player.Render();
}

void Level::CreatePillar(int index, float offset)
{
	Pillar& pillar = pillars[index];

	pillar.TopPosition.x = offset;
	pillar.BottomPosition.x = offset;
	pillar.TopPosition.z = index * 0.1f - 0.5f;
	pillar.BottomPosition.z = index * 0.1f - 0.5f + 0.05f;

	float center = Random::Float() * 35.0f - 17.5f;
	float gap = 2.0f + Random::Float() * 5.0f;

	pillar.TopPosition.y = 10.0f - ((10.0f - center) * 0.2f) + gap * 0.5f;
	pillar.BottomPosition.y = -10.0f - ((-10.0f - center) * 0.2f) - gap * 0.5f;
}

bool Level::CollisionTest()
{
	if (glm::abs(player.GetPosition().y) > 8.5f)
		return true;

	glm::vec4 playerVertices[4] = {
		{ -0.5f, -0.5f, 0.0f, 1.0f },
		{  0.5f, -0.5f, 0.0f, 1.0f },
		{  0.5f,  0.5f, 0.0f, 1.0f },
		{ -0.5f,  0.5f, 0.0f, 1.0f }
	};

	const auto& pos = player.GetPosition();
	glm::vec4 playerTransformedVerts[4];
	for (int i = 0; i < 4; i++)
	{
		playerTransformedVerts[i] = glm::translate(glm::mat4(1.0f), { pos.x, pos.y, 0.0f })
			* glm::rotate(glm::mat4(1.0f), glm::radians(player.GetRotation()), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { 1.0f, 1.3f, 1.0f })
			* playerVertices[i];
	}


	// To match Triangle.png (each corner is 10% from the texture edge)
	glm::vec4 pillarVertices[3] = {
		{ -0.5f + 0.1f, -0.5f + 0.1f, 0.0f, 1.0f },
		{  0.5f - 0.1f, -0.5f + 0.1f, 0.0f, 1.0f },
		{  0.0f + 0.0f,  0.5f - 0.1f, 0.0f, 1.0f },
	};

	for (auto& p : pillars)
	{
		glm::vec2 triangle[3];
		
		for (int i = 0; i < 3; i++)
		{
			triangle[i] = glm::translate(glm::mat4(1.0f), { p.TopPosition.x, p.TopPosition.y, 0.0f })
				* glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), { 0.0f, 0.0f, 1.0f })
				* glm::scale(glm::mat4(1.0f), { p.TopScale.x, p.TopScale.y, 1.0f })
				* pillarVertices[i];
		}

		for (auto& vert : playerTransformedVerts)
		{
			if (PointInTriangle({ vert.x, vert.y }, triangle[0], triangle[1], triangle[2]))
				return true;
		}

		for (int i = 0; i < 3; i++)
		{
			triangle[i] = glm::translate(glm::mat4(1.0f), { p.BottomPosition.x, p.BottomPosition.y, 0.0f })
				* glm::scale(glm::mat4(1.0f), { p.BottomScale.x, p.BottomScale.y, 1.0f })
				* pillarVertices[i];
		}

		for (auto& vert : playerTransformedVerts)
		{
			if (PointInTriangle({ vert.x, vert.y }, triangle[0], triangle[1], triangle[2]))
				return true;
		}

	}
	return false;
}

void Level::GameOver()
{
	gameOverFlag = true;
}

void Level::Reset()
{
	gameOverFlag = false;

	player.Reset();

	pillarTarget = 30.0f;
	pillarIndex = 0;
	for (int i = 0; i < 5; i++)
		CreatePillar(i, i * 10.0f);
}