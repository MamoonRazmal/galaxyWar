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
	private:
		void Move(float deltaTime);
		Actor* mOwner;
		float mSpeed;
		float mDamage;
	};
}