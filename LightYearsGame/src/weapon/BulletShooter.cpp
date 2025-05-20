#include "weapon/BulletShooter.h"
#include "framework/Core.h"
namespace ly
{
	ly::BulletShooter::BulletShooter(Actor* Actor ,float cooldownTime) :Shooter{ Actor }, mCooldownClock{},mCooldownTime{cooldownTime}
	{
	}

	bool BulletShooter::IsOnCoolDown() const
	{
		if (mCooldownClock.getElapsedTime().asSeconds() > mCooldownTime)
		{
			return false;
		}
		return true;
	}

	void BulletShooter::ShootImpl()
	{
		mCooldownClock.restart();
		LOG("Shooting!");
	}

}
