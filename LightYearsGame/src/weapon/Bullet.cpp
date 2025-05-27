#include "weapon/Bullet.h"

namespace ly
{
	ly::Bullet::Bullet(World* world, Actor* owner, std::string& texturePath, float speed, float damage)
		:Actor{world,texturePath},mOwner{owner},mSpeed{speed},mDamage{damage}
	{
	}
	void Bullet::SetDamage(float damage)
	{
		mDamage = damage;
	}

	void Bullet::SetSpeed(float speed)
	{
		mSpeed = speed;
	}

	void Bullet::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		Move(deltaTime);
		if (IsActorOutOfWindowBounds())
		{
			Destroy();
		}
	}

	void Bullet::BeginPlay()
	{
		Actor::BeginPlay();
		SetEnablePhysics(true);

	}

	void Bullet::Move(float deltaTime)
	{

		AddActorLocationOffset(GetActorForwardDirection() * mSpeed * deltaTime );
	}
	


}
