#pragma once
#include "LMonsterWeapon.h"
namespace cl
{
	class KnightEffect;
	class KnightWeapon : public MonsterWeapon
	{
	public:
		KnightWeapon(Scene* sc);
		~KnightWeapon();
	protected:
		virtual void SetAnimation() override;
		virtual void SetSprite() override;
		virtual void OnBeatChanged() override;
		virtual void PlayAttackAnimation(Vector2 dir) override;
	private:
		KnightEffect* mEffect;
	};
}

