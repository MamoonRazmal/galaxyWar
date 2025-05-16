#pragma once
#include "framework/Core.h"
namespace ly
{
	class Actor;
	class Application;
	class World
	{
	public:
		World(Application* ownapp);
		
		void BeginPlayInternel();
		void TickInternal(float deltaTime);
		template <typename ActorType>
		weak<ActorType> spawnActor();
		
		virtual ~World();
	private:
		void BeginPlay();
		void Tick(float delta);
		Application* mOwningApp;
		bool mBeganPlay;
		List<shared<Actor>> mActors;
		List<shared<Actor>> mpendingActors;



	};
	
	template<typename ActorType>
	 weak<ActorType> World::spawnActor()
	{
		shared<ActorType> newActor{ new ActorType{this} };
		mpendingActors.push_back(newActor);
		return newActor;
	}

}
