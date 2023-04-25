#pragma once
#include "LuciEngine.h"
namespace cl
{
	class Cadence;
	class Health
	{
	public:
		Health(Cadence* player);
		~Health();
		void OnDamage(float damage);
		void OnHeal(float heal);
		void Reset();
	private:
		void SetHeart();
		void OnHealthIsZero();

		static float _defaultMaxHealth;
		static float _currentMaxHealth;
		static float _currentHealth;

		Vector2 startPosition;
		
		float mMaxHealth;
		float mHealth;
		Cadence* mPlayer;
	};
}

