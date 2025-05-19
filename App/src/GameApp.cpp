#include <Chill.h>
#include <Chill/Core/EntryPoint.h>

#include "GameLayer.h"

class GameApp : public Chill::Application
{
public:
	GameApp()
	{
		AddLayer(new GameLayer());
	}

	~GameApp()
	{
	}
};

Chill::Application* Chill::CreateApplication()
{
	return new GameApp();
}