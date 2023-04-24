#include "LFireballEffect.h"
#include "LAnimator.h"
#include "LBeatManager.h"
namespace cl
{
	FireballEffect::FireballEffect(Scene* sc)
		:WeaponEffect(sc)
	{
	}
	FireballEffect::~FireballEffect()
	{
	}
	void FireballEffect::Initialize()
	{
		WeaponEffect::Initialize();

		std::wstring rightPath = L"..\\Assets\\Arts\\Effects\\AttackSwipes\\Fireball\\Fireball_Right.bmp";
		std::wstring leftPath = L"..\\Assets\\Arts\\Effects\\AttackSwipes\\Fireball\\Fireball_Left.bmp";
		for (int i = 0; i < 5; ++i)
		{
			mRightAnim[i] = L"FireballRight " + std::to_wstring(i);
			mLeftAnim[i] = L"FireballLeft" + std::to_wstring(i);
			mAnimator->CreateAnimation(mRightAnim[i], L"FireballRight", rightPath, 7, 5, 0, i, 7, Vector2::Zero, BeatManager::BeatDuration());
			mAnimator->CreateAnimation(mLeftAnim[i], L"FireballLeft", leftPath, 7, 5, 0, i, 7, Vector2::Zero, BeatManager::BeatDuration());
		}
	}
	void FireballEffect::SetIndex(int index)
	{
		mIndex = index;
		if (mIndex >= 5)
			mIndex = mIndex % 4 + 1;
	}
	void FireballEffect::PlayRight()
	{
		mTransform->SetLocalPos(Vector2::Right * UNITLENGTH * (mIndex + 1));
		mAnimator->Play(mRightAnim[mIndex], Animator::PlaySetting::Once, false);
	}
	void FireballEffect::PlayLeft()
	{
		mTransform->SetLocalPos(Vector2::Left * UNITLENGTH * (mIndex + 1));
		mAnimator->Play(mLeftAnim[mIndex], Animator::PlaySetting::Once, false);
	}
}