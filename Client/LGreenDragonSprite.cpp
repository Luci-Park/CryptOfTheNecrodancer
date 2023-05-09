#include "LGreenDragonSprite.h"
#include "LAnimator.h"
namespace cl
{
	GreenDragonSprite::GreenDragonSprite(Scene* sc)
		:CharacterSprite(sc)
	{
	}
	GreenDragonSprite::~GreenDragonSprite()
	{
	}
	void GreenDragonSprite::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		CharacterSprite::Initialize();
		std::wstring path = L"..\\Assets\\Arts\\Miniboss\\Dragon\\GreenDragon.bmp";
		mLeftAnimation = L"Left";
		mRightAnimation = L"Right";
		mLeftShadowAnimation = L"Shadow";
		mRightShadowAnimation = L"Shadow";

		mAnimator->CreateAnimation(mLeftAnimation, L"GreenDragon", path, 8, 2, 0, 0, 4, -Vector2(27, 51), Conductor::Instance().SecondsPerBeat());
		mAnimator->CreateAnimation(mRightAnimation, L"GreenDragon", path, 8, 2, 4, 0, 4, -Vector2(27, 51), Conductor::Instance().SecondsPerBeat());
		mAnimator->CreateAnimation(mLeftShadowAnimation, L"GreenDragon", path, 8, 2, 0, 1, 4, -Vector2(27, 51), Conductor::Instance().SecondsPerBeat());
		mAnimator->CreateAnimation(mRightShadowAnimation, L"GreenDragon", path, 8, 2, 4, 1, 4, -Vector2(27, 51), Conductor::Instance().SecondsPerBeat());
		Turn(Vector2::Right);
	}
	void GreenDragonSprite::Turn(Vector2 dir)
	{
		if (dir == Vector2::Left || dir == Vector2::Right)
			mLookDir = dir;
		if (mLookDir == Vector2::Left)
		{
			if (!mbInShadows)
				mAnimator->Play(mLeftAnimation, Animator::PlaySetting::Loop, false);
			else
				mAnimator->Play(mLeftShadowAnimation, Animator::PlaySetting::Loop, false);
		}
		else if (mLookDir == Vector2::Right)
		{
			if (!mbInShadows)
				mAnimator->Play(mRightAnimation, Animator::PlaySetting::Loop, true);
			else
				mAnimator->Play(mRightShadowAnimation, Animator::PlaySetting::Loop, true);
		}
	}
}
