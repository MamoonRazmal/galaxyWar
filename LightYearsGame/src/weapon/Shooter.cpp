#include "weapon/Shooter.h"

namespace ly
{
	void Shooter::Shoot()
	{
		if (CanShoot() && !IsOnCoolDown())
		{
			ShootImpl();

		}
	}
	ly::Shooter::Shooter(Actor* owner) : mOwner{owner}
	{
	}

}
