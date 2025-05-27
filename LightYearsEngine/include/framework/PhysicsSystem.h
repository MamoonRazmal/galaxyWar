#pragma once
#include "framework/Core.h"
#include <box2d/box2d.h>


#include "framework/Actor.h"
namespace ly
{
//#include "../../../build/_deps/box2d-src/src/world.h"
class PhyiscsContactListener : public b2ContactListener
{
	virtual void BeginContact(b2Contact* contact)override;
	virtual void EndContact(b2Contact* contact)override;
};

	class PhysicsSystem
	{
	public :
		static PhysicsSystem& Get();
		void step(float deltaTime);
		
		b2Body* AddListener(Actor* Listener);
		float GetPhysicScale()const { return mPhysicsScale; }
		void RemoveListener(b2Body* bodytoremove);
		static void cleanup();
	protected:
		PhysicsSystem();
	private:
		static unique<PhysicsSystem> physicsSystem;
		b2Vec2 gravity;
		float mPhysicsScale;
		b2World mPhysicworld;
		int mVelocityIteration;
		int mPositionIteration;
		PhyiscsContactListener mContactListener;
		Set<b2Body*> mPendingRemoveListeners;
		void ProcessPendingRemoveListeners();
	};
}

