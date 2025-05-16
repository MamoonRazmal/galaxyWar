#include "framework/World.h"
#include "framework/Core.h"
#include "framework/Actor.h"
namespace ly
{
	World::World(Application* owningApp):mOwningApp{ owningApp },mBeganPlay{false},mActors{},mpendingActors{}
	{

	}
	void World::BeginPlayInternel()
	{
		if (!mBeganPlay)
		{
			mBeganPlay = true;
			BeginPlay();
		}
	}
	void World::TickInternal(float deltaTime)
	{
		for (shared <Actor> actor : mpendingActors)
		{
			mActors.push_back(actor);
			actor->BeginPlayInteral();
		}
		mpendingActors.clear();
		for (shared<Actor> actor : mActors)
		{
			actor->Tick(deltaTime);
		}
		
		Tick(deltaTime);

	}
	World::~World()
	{
	}
	void World::BeginPlay()
	{
		LOG("Begin Play ");
	}
	void World::Tick(float delta)
	{
		LOG("ticking at framerate : %f\n", 1.f / delta);
	}
}