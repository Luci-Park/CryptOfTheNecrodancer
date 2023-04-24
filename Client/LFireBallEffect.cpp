#include "LFireballEffect.h"
#include "LAnimator.h"
#include "LBeatManager.h"
#include "LLightSource.h"
namespace cl
{
	FireballEffect::FireballEffect(Scene* sc)
		: WeaponEffect(sc)
		, mIndex(0)
	{
		mLight = new LightSource(mTransform, 0, 4.25);
	}
	FireballEffect::~FireballEffect()
	{
		delete mLight;
		mLight = nullptr;
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
	void FireballEffect::Update()
	{
		WeaponEffect::Update();
		if (mAnimator->IsComplete())
			mLight->SetBrightness(0, 0);
		else
			mLight->SetBrightness(0, 4.25);
	}
	void FireballEffect::SetIndex(int index)
	{
		mIndex = index;
	}
	void FireballEffect::PlayRight()
	{
		int playIndex = mIndex >= 5 ? (mIndex % 4) + 1 : mIndex;
		mTransform->SetLocalPos(Vector2::Right * UNITLENGTH * (mIndex + 1));
		mAnimator->Play(mRightAnim[playIndex], Animator::PlaySetting::Once, false);
	}
	void FireballEffect::PlayLeft()
	{
		int playIndex = mIndex >= 5 ? (mIndex % 4) + 1 : mIndex;
		mTransform->SetLocalPos(Vector2::Left * UNITLENGTH * (mIndex + 1));
		mAnimator->Play(mLeftAnim[playIndex], Animator::PlaySetting::Once, true);
	}
}