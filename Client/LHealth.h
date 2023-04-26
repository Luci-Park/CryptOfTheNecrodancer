#pragma once
#include "LuciEngine.h"
namespace cl
{
	class HeartUI;
	class Cadence;
	class Health
	{
	public:
		Health(Cadence* player);
		~Health();
		void OnDamage(float damage);
		void OnHeal(float heal);
		void Reset();
		float CurrentHealth() { return mHealth; }
	private:
		void SetHeart();
		void OnHealthIsZero();

		static float _defaultMaxHealth;
		static float _currentMaxHealth;
		static float _currentHealth;

		Vector2 startPosition;
		float unitLength;
		std::vector<HeartUI*> mHeartUI;
		float mMaxHealth;
		float mHealth;
		Cadence* mPlayer;
	};
}

