#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "config.h"
ly::Application* GetApplication()
{
	return new ly::GameApplication{};
}
namespace ly
{
	GameApplication::GameApplication():Application{600,900,"Light Years",sf::Style::Titlebar | sf::Style::Close}
	{
		weak<World> newWorld = LoadWorld<World>();
		newWorld.lock()->spawnActor<Actor>();
		ActorToDestroy = newWorld.lock()->spawnActor<Actor>();
		ActorToDestroy.lock()->setTexture(GetResourceDir() + "SpaceShooterRedux/PNG/playerShip1_blue.png");
		counter = 0;

	}
	void GameApplication::Tick(float deltaTime)
	{
		counter += deltaTime;
		if (counter > 2.f)
		{
			if (!ActorToDestroy.expired())
			{
				ActorToDestroy.lock()->Destroy();
			}
		}
	}
}