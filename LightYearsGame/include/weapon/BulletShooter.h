#pragma once
#include "weapon/Shooter.h"
#include <SFML/System.hpp>
namespace ly
{
	class BulletShooter : public Shooter
	{
	public :
		BulletShooter(Actor* Actor ,float cooldownTime = 1.f);
		virtual bool IsOnCoolDown() const override;

	private:
		sf::Clock mCooldownClock;
		float mCooldownTime;
		virtual void ShootImpl()override;
		
	};

}