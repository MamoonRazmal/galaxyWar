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
		//mHealthComp.OnHealthChanged.Broadcast(11, 89, 100);
		Delegate<float, float, float>onTakenDamage;
		Delegate<>onHealthEmpty;

		
	private:
		float mHealth;
		float mMaxHealth;
		void TakenDamage(float amount);
		void HealthEmpty();
		void HealthRegain(float regain);
	};
}