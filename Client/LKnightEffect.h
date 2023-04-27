#pragma once
#include "LWeaponEffect.h"
#include "LKnight.h"
namespace cl
{
	class KnightEffect : public WeaponEffect
	{
	public:
		KnightEffect(Scene* sc);
		virtual ~KnightEffect();
		virtual void Initialize() override;
		virtual void PlayEffect(Vector2 direction);
	private:
		std::wstring mAttackAnimation[(int)Knight::AttackDir::Size];

		virtual void PlayUp()   {};
		virtual void PlayDown() {};
		virtual void PlayRight(){};
		virtual void PlayLeft() {};
	};
}

