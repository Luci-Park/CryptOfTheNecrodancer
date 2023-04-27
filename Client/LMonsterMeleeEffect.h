#pragma once
#include "LWeaponEffect.h"
namespace cl
{
	class MonsterMeleeEffect : public WeaponEffect
	{
	public:
		MonsterMeleeEffect(Scene* sc);
		virtual ~MonsterMeleeEffect();
		virtual void Initialize() override;

	protected:
		virtual void PlayUp();
		virtual void PlayDown();
		virtual void PlayRight();
		virtual void PlayLeft();

		std::wstring mUpAnim;
		std::wstring mDownAnim;
		std::wstring mRightAnim;
		std::wstring mLeftAnim;

	};
}

