#include "framework/PhysicsSystem.h"

#include <box2d/box2d.h>
#include <box2d/b2_contact.h>

#include "framework/Actor.h"
#include <box2d/b2_body.h>
#include "framework/MathUtility.h"
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>




namespace ly
{
	
	unique< PhysicsSystem> PhysicsSystem::physicsSystem{ nullptr };
	PhysicsSystem& ly::PhysicsSystem::Get()
	{
		if (!physicsSystem)
		{
			physicsSystem = std::move(unique<PhysicsSystem>{new PhysicsSystem});
		}
		return *physicsSystem;
	}

	void PhysicsSystem::step(float deltaTime)
	{
		ProcessPendingRemoveListeners();
		mPhysicworld.Step(deltaTime, mVelocityIteration, mPositionIteration);
	}

	b2Body* PhysicsSystem::AddListener(Actor* Listener)
	{
		if (Listener->IsPendingDestroy()) return nullptr;

		
			b2BodyDef bodydef;
			bodydef.type = b2_dynamicBody;
			bodydef.userData.pointer = reinterpret_cast<uintptr_t>(Listener);
			bodydef.position.Set(Listener->GetActorLocation().x* GetPhysicScale(), Listener->GetActorLocation().y* GetPhysicScale());
			bodydef.angle = DegreesToRadians( Listener->GetActorRotation().asDegrees());
			b2Body* body = mPhysicworld.CreateBody(&bodydef);
			b2PolygonShape shape;
			auto bound = Listener->GetActorGlobalBounds();
			shape.SetAsBox(bound.size.x/2.f * GetPhysicScale(), bound.size.y / 2.f * GetPhysicScale());
			b2FixtureDef fixtureDef;
			fixtureDef.shape = &shape;
			fixtureDef.density = 1.0f;
			fixtureDef.friction = 0.3f;
			fixtureDef.isSensor = true;
			body->CreateFixture(&fixtureDef);
			return body;
	}

	void PhysicsSystem::RemoveListener(b2Body* bodytoremove)
	{
		//Too:remove b2body...
		mPendingRemoveListeners.insert(bodytoremove);
	}

	void PhysicsSystem::cleanup()
	{
		if (!physicsSystem)
		{
			physicsSystem = std::move(unique<PhysicsSystem>{new PhysicsSystem});
		}
		

	}

	PhysicsSystem::PhysicsSystem() :mPhysicworld{ b2Vec2({0.0f,0.0f})}, mPhysicsScale{0.01f},mVelocityIteration{8},mPositionIteration{3}, mContactListener{},mPendingRemoveListeners{}
	{
		mPhysicworld.SetContactListener(&mContactListener);
		mPhysicworld.SetAllowSleeping(false);
	}

	void PhysicsSystem::ProcessPendingRemoveListeners()
	{
		for (auto listener : mPendingRemoveListeners)
		{
			mPhysicworld.DestroyBody(listener);
		}
		mPendingRemoveListeners.clear();
	}



void PhyiscsContactListener::BeginContact(b2Contact* contact)
{
	Actor* ActorA = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
	Actor* ActorB = reinterpret_cast<Actor*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);
	LOG("Begin contact");
	if (ActorA && !ActorA->IsPendingDestroy())
	{
		ActorA->OnActorBeginOverlap(ActorB);
	}
	if (ActorB && ActorB->IsPendingDestroy())
	{
		ActorB->OnActorBeginOverlap(ActorA);
	}

}

void PhyiscsContactListener::EndContact(b2Contact* contact)
{
	LOG("End contact");
	Actor* ActorA = nullptr;
	Actor* ActorB = nullptr;
	if (contact->GetFixtureA() && contact->GetFixtureA()->GetBody())
	{
		 ActorA = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
	}
	if (contact->GetFixtureB() && contact->GetFixtureB()->GetBody())
	{
		ActorB = reinterpret_cast<Actor*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);
	}

	if (ActorA && !ActorA->IsPendingDestroy())
	{
		ActorA->OnActorEndOverlap(ActorB);
	}
	if (ActorB && ActorB->IsPendingDestroy())
	{
		ActorB->OnActorEndOverlap(ActorA);
	}

}
}