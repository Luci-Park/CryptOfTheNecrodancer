#pragma once
#include "LWeaponEffect.h"
namespace cl
{
	class FireballEffect : public WeaponEffect
	{
	public:
		FireballEffect(Scene* sc);
		virtual ~FireballEffect();
		virtual void Initialize();
		void SetIndex(int index);
	protected:
		virtual void PlayUp() {}
		virtual void PlayDown() {}
		virtual void PlayRight();
		virtual void PlayLeft();

		std::wstring mRightAnim[5];
		std::wstring mLeftAnim[5];
		int mIndex;
	};
}

