#pragma once
#include "framework/Actor.h"

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
	private:
		sf::Vector2f mVelocity;
		
	};
}