#pragma once
#include "LWeaponEffect.h"
namespace cl
{
	class LightSource;
	class FireballEffect : public WeaponEffect
	{
	public:
		FireballEffect(Scene* sc);
		virtual ~FireballEffect();
		virtual void Initialize() override;
		virtual void Update() override;
		void SetIndex(int index);
	protected:
		virtual void PlayUp() {}
		virtual void PlayDown() {}
		virtual void PlayRight();
		virtual void PlayLeft();

		std::wstring mRightAnim[5];
		std::wstring mLeftAnim[5];
		int mIndex;
		LightSource* mLight;
	};
}

