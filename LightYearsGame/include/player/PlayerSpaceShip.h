#pragma once
#include "spaceship/Spaceship.h"

namespace ly
{
	class BulletShooter;
	class PlayerSpaceship :public Spaceship
	{
	public:
		PlayerSpaceship(World* ownworld, const std::string& path = "SpaceShooterRedux/PNG/playerShip1_blue.png");
		virtual void Tick(float deltaTime)override;
		void setSpeed(float speed) { mSpeed = speed; }
		float  GetSpeed() { return mSpeed; }
		virtual void Shoot()override;
		void LimitBorder();
	private:
		void HandleInput();
		void ConsumeInput(float deltaTime);
		void NormalizeInput();
		sf::Vector2f mMoveInput;
		float mSpeed;
		unique<BulletShooter> mShooter;
	};
}