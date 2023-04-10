#pragma once
#include "LWeapon.h"
namespace cl
{
	class ShortMeleeEffect;
	class Dagger : public Weapon
	{
	public:
		Dagger(Scene* sc);
		~Dagger();

	protected:
		virtual void SetAnimation() override;
		virtual void SetSprite() override;
		virtual void OnBeatChanged() override;
		virtual bool TryAttack(Vector2 srcIdx, Vector2 input) override;
		virtual void PlayAttackAnimation(Vector2 dir) override;
	private:
		ShortMeleeEffect* mEffect;
	};
}
