#pragma once
#include "LWeaponEffect.h"
namespace cl
{
	class KnightEffect : public WeaponEffect
	{
	public:
		KnightEffect(Scene* sc);
		virtual ~KnightEffect();
		virtual void Initialize() override;
		virtual void PlayEffect(Vector2 direction);
	};
}

