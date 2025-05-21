#pragma once
#include "framework/Core.h"
#include <SFML/Graphics.hpp>
#include "framework/Application.h"
namespace ly
{
	class Actor;
	//class Application;
	class World
	{
	public:
		World(Application* ownapp);
		
		void BeginPlayInternel();
		void TickInternal(float deltaTime);
		void Render(sf::RenderWindow& window);
		template <typename ActorType , typename... Args>
		weak<ActorType> spawnActor(Args... args);
		sf::Vector2u GetWindowSize()const { return mOwningApp->GetWindowSize(); }
		void CleanCycle();
		virtual ~World();
	private:
		void BeginPlay();
		void Tick(float delta);
		Application* mOwningApp;
		bool mBeganPlay;
		List<shared<Actor>> mActors;
		List<shared<Actor>> mpendingActors;



	};
	
	template<typename ActorType,typename... Args>
	 weak<ActorType> World::spawnActor(Args... args)
	{
		shared<ActorType> newActor{ new ActorType(this, args...)};
		mpendingActors.push_back(newActor);
		return newActor;
	}

}
