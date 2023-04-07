#pragma once
#include "LWeapon.h"
namespace cl
{
	class MonsterWeapon : public Weapon
	{
	public:
		MonsterWeapon(Scene* sc);
		~MonsterWeapon();
		

		void SetPower(float power) { mPower = power; }
	protected:
		virtual void SetSprite() override;
		virtual void SetAnimation();
		virtual Vector2 EffectPos(Vector2 dir);
		virtual std::wstring SelectAnimation(Vector2 dir);
		virtual bool TryAttack(Vector2 srcIdx, Vector2 input);
	private:
		std::wstring mUpAnimation;
		std::wstring mDownAnimation;
		std::wstring mLeftAnimation;
		std::wstring mRightAnimation;
	};
}