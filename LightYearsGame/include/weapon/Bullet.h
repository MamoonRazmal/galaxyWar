#pragma once
#include "framework/Actor.h"
namespace ly
{
	class Bullet :public Actor
	{
	public:
		Bullet(World* world, Actor* owner, std::string& texturePath, float speed =600.f, float damage = 10.f);
		void SetDamage(float damage);
		void SetSpeed(float speed);
		virtual void Tick(float deltaTime)override;
		virtual void BeginPlay()override;
		float getDamage() const
		{
			return mDamage;
		}
	private:
		void Move(float deltaTime);
		virtual void OnActorBeginOverlap(Actor* other) override;
		Actor* mOwner;
		float mSpeed;
		float mDamage;
	};
}