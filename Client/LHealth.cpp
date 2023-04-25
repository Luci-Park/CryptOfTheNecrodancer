#include "LHealth.h"

namespace cl
{
	Health::Health(Cadence* player)
		: mPlayer(player)
	{
		mMaxHealth = _currentMaxHealth;
		mHealth = _currentHealth;
	}
	Health::~Health()
	{
		_currentMaxHealth = mMaxHealth;
		_currentHealth = mHealth;
	}
	void Health::OnDamage(float damage)
	{
		mHealth -= damage;
		if (mHealth <= 0)
			OnHealthIsZero();
	}
	void Health::OnHeal(float heal)
	{
		mHealth = std::clamp(mHealth + heal, 0.0f, mMaxHealth);
	}
	void Health::SetHeart()
	{
	}
	void Health::OnHealthIsZero()
	{
	}
	void Health::Reset()
	{
		mMaxHealth = _defaultMaxHealth;
		mHealth = _currentHealth;
	}
}
