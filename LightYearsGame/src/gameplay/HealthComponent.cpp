
#include <gameplay/HealthComponent.h>
#include <framework/Core.h>

ly::HealthComponent::HealthComponent(float health, float maxHealths):mHealth{health},mMaxHealth{ maxHealths }
{
}

void ly::HealthComponent::ChangeHealth(float amt)
{
	if (amt == 0)
		return;
	if (mHealth == 0)return ;
	mHealth += amt;
	if (mHealth < 0)
	{
		mHealth = 0;
	}
	if (mHealth > mMaxHealth)
	{
		mHealth = mMaxHealth;
	}
	if (amt < 0)
	{
		TakenDamage(-amt);
		if (mHealth <= 0)
		{
			HealthEmpty();
		}
		

		onTakenDamage.Broadcast(amt, mHealth, mMaxHealth);
	}
}

void ly::HealthComponent::TakenDamage(float amount)
{
	onTakenDamage.Broadcast(amount, mHealth, mMaxHealth);
}

void ly::HealthComponent::HealthEmpty()
{
	onHealthEmpty.Broadcast();
}

void ly::HealthComponent::HealthRegain(float heal)
{
	LOG("Health Regain : %f", heal);
}
