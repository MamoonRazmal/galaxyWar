#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/Actor.h"
namespace ly
{
	ly::Actor::Actor(World* ownworld):mOwningWorld{ownworld},mHasBeganPlay{false}
	{
	}
	void Actor::BeginPlayInteral()
	{
		if (!mHasBeganPlay)
		{
			mHasBeganPlay = true;
			BeginPlay();
		}
	}
	void Actor::BeginPlay()
	{
		LOG("Actor begin play");
	}
	void Actor::Tick(float deltatyme)
	{
		LOG("user is ticking");
	}
	ly::Actor::~Actor()
	{
	}
}

