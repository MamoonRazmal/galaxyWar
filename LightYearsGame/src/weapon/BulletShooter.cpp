#include "weapon/BulletShooter.h"
#include "framework/Core.h"
#include "weapon/Bullet.h"
#include "framework/World.h"
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
		sf::Angle angle = sf::degrees({ 260.0f });
		std::string path = "SpaceShooterRedux/PNG/Lasers/laserBlue01.png";
		weak<Bullet> newBullet = GetOwner()->GetWorld()->spawnActor<Bullet>(GetOwner(), path);
		newBullet.lock()->SetActorLocation(GetOwner()->GetActorLocation());
		newBullet.lock()->setActorRotation(GetOwner()->GetActorRotation()+ angle);
		//LOG("Shooting!");
	}

}
