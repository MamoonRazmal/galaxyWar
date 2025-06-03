#include "weapon/Bullet.h"

namespace ly
{
	ly::Bullet::Bullet(World* world, Actor* owner, std::string& texturePath, float speed, float damage)
		:Actor{world,texturePath},mOwner{owner},mSpeed{speed},mDamage{damage}
	{
		SetTeamID(owner->GetTeamID());
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

	void Bullet::OnActorBeginOverlap(Actor* other)
	{
		if (IsOtherHostile(other))
		{
			other->ApplyDamage(getDamage());
			Destroy();
		}

	}
	


}
