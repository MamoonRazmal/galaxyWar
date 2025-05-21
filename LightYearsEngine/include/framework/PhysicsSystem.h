#pragma once
#include "framework/Core.h"
#include <box2d/box2d.h>




//#include "../../../build/_deps/box2d-src/src/world.h"
namespace ly
{
	class PhysicsSystem
	{
	public :
		static PhysicsSystem& Get();
		void step(float deltaTime);
		b2Body* AddListener(Actor* Listener);
	protected:
		PhysicsSystem();
	private:
		static unique<PhysicsSystem> physicsSystem;
		b2Vec2 gravity;
		float mPhysicsScale;
		b2World mPhysicworld;
		int mVelocityIteration;
		int mPositionIteration;
	};
}

