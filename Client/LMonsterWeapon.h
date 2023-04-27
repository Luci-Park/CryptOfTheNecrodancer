#pragma once
#include "LWeapon.h"
namespace cl
{
	class MonsterMeleeEffect;
	class MonsterWeapon : public Weapon
	{
	public:
		MonsterWeapon(Scene* sc);
		virtual ~MonsterWeapon();

		void SetPower(float power) { mPower = power; }
	protected:
		virtual void SetAnimation() override;
		virtual void SetSprite() override;
		virtual void OnBeatChanged() override;
		virtual bool TryAttack(Vector2 srcIdx, Vector2 input) override;
		virtual void PlayAttackAnimation(Vector2 dir) override;
	private:
		MonsterMeleeEffect* mEffect;
	};
}