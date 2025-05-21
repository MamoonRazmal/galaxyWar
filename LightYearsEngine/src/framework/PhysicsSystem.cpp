#include "framework/PhysicsSystem.h"

#include <box2d/box2d.h>
#include "framework/PhysicsSystem.h"
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

	PhysicsSystem::PhysicsSystem() :mPhysicworld{ b2Vec2({0.0f,0.0f})}, mPhysicsScale{0.01f},mVelocityIteration{8},mPositionIteration{3}
	{

	}

}
