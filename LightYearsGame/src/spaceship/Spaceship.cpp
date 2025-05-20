#include "spaceship/Spaceship.h"
#include "framework/Actor.h"


namespace ly
{
	Spaceship::Spaceship(World* ownworld, const std::string& texturePath):Actor{ownworld,texturePath},mVelocity{}
	{
	}

	void Spaceship::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		AddActorLocationOffset(getVelocity() *deltaTime);
	}

	void Spaceship::SetVelocity(const sf::Vector2f& newVol)
	{
		mVelocity = newVol;
	}

	sf::Vector2f Spaceship::getVelocity()
	{
		return mVelocity;
	}

	void Spaceship::Shoot()
	{
	}

}
