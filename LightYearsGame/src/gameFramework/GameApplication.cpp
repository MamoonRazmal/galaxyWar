#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "spaceship/Spaceship.h"
#include "framework/AssetManager.h"
#include "player/PlayerSpaceShip.h"
#include "config.h"
ly::Application* GetApplication()
{
	return new ly::GameApplication{};
}
namespace ly
{
	GameApplication::GameApplication():Application{600,900,"Light Years",sf::Style::Titlebar | sf::Style::Close}
	{
		AssetManager::Get().SetAssetRootDirectory(GetResourceDir());
		weak<World> newWorld = LoadWorld<World>();
		newWorld.lock()->spawnActor<Actor>();
		testPlayerSpaceShip = newWorld.lock()->spawnActor<PlayerSpaceship>();
		testPlayerSpaceShip.lock()->setTexture(GetResourceDir() + "SpaceShooterRedux/PNG/playerShip1_blue.png");
		testPlayerSpaceShip.lock()->SetActorLocation(sf::Vector2f(300, 299));
		sf::Angle a = sf::degrees({ 0.f });
		testPlayerSpaceShip.lock()->setActorRotation(a);
		

	}
	void GameApplication::Tick(float deltaTime)
	{
		
	}
}