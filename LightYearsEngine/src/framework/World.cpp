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
		for (auto iter = mActors.begin();iter != mActors.end();)
		{
			if (iter->get()->IsPendingDestroy())
			{
				iter = mActors.erase(iter);
			}
			else
			{
				iter->get()->Tick(deltaTime);
				++iter;
			}
		}
		
		Tick(deltaTime);

	}
	void World::Render(sf::RenderWindow& window)
	{
		for (auto& actor : mActors)
		{
			actor->Render(window);
		}
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