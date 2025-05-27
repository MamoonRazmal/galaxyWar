#pragma once
#include "framework/Delegate.h"
namespace ly
{
	class HealthComponent
	{
	public :
		HealthComponent(float health, float maxHealth);
		void ChangeHealth(float amt);
		float getHealth() const { return mHealth; };
		float getMaxHealth()const { return mMaxHealth; };
		Delegate<float, float, float>OnHealthChanged;
		
	private:
		float mHealth;
		float mMaxHealth;
		void TakenDamage(float amount);
		void HealthEmpty();
		void HealthRegain(float regain);
	};
}