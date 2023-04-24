#pragma once
#include "LWeapon.h"
#include "LFireballEffect.h"
namespace cl
{
	class DragonFireball : public Weapon
	{
	public:
		DragonFireball(Scene* sc);
		~DragonFireball();
	protected:
		virtual void SetAnimation() override;
		virtual void SetSprite() override;
		virtual void OnBeatChanged() override;
		virtual bool TryAttack(Vector2 srcIdx, Vector2 input) override;
		virtual void PlayAttackAnimation(Vector2 dir) override;

		std::vector<FireballEffect*> mFireballEffects;
		int length;
	};
}

