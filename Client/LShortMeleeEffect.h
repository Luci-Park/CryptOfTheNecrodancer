#pragma once
#include "LWeaponEffect.h"
namespace cl
{
	class ShortMeleeEffect : public WeaponEffect
	{
	public:
		ShortMeleeEffect(Scene* sc);
		~ShortMeleeEffect();
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

