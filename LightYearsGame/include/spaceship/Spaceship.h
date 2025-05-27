#pragma once
#include "framework/Actor.h"
#include <gameplay/HealthComponent.h>

namespace ly
{
	class Spaceship : public Actor
	{
	public :
		Spaceship(World* ownworld, const std::string& texturePath = "");
		virtual void Tick(float deltaTime) override;
		void SetVelocity(const sf::Vector2f& newVol);
		sf::Vector2f getVelocity();
		virtual void Shoot();
		virtual void BeginPlay()override;
	private:
		sf::Vector2f mVelocity;
		void OnHealthChanged(float amt, float health, float maxhealth);
		HealthComponent mHealthComp;
		
	};
}