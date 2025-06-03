#include "spaceship/Spaceship.h"
#include "framework/Actor.h"




namespace ly
{
	Spaceship::Spaceship(World* ownworld, const std::string& texturePath):Actor{ownworld,texturePath},mVelocity{},mHealthComp{100.f,100.f}
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

	void Spaceship::BeginPlay()
	{
		Actor::BeginPlay();
		SetEnablePhysics(true);
		weak<Object> selfRef = GetSelfWeakRef();
		mHealthComp.OnHealthChanged.BindAction(GetSelfWeakRef(), &Spaceship::OnHealthChanged);
		mHealthComp.onTakenDamage.BindAction(GetSelfWeakRef(), &Spaceship::OnTakenDamage);
		mHealthComp.onHealthEmpty.BindAction(GetSelfWeakRef(), &Spaceship::Blow);
		
	}

	void Spaceship::ApplyDamage(float amt)
	{
		mHealthComp.ChangeHealth(-amt);
	}

	void Spaceship::OnHealthChanged(float amt, float health, float maxhealth)
	{
		LOG("healthchanged by :%f and now is %f/%f", amt, health, maxhealth);
	}

	void Spaceship::OnTakenDamage(float amt, float health, float maxhealth)
	{

	}

	void Spaceship::Blow()
	{
		Destroy();
	}

}
