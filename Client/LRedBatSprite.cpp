#include "LRedBatSprite.h"
#include "LAnimator.h"
namespace cl
{
	RedBatSprite::RedBatSprite(Scene* sc)
		:CharacterSprite(sc)
	{
	}
	void RedBatSprite::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		CharacterSprite::Initialize();

		std::wstring leftPath = L"..\\Assets\\Arts\\Monsters\\Bats\\Bats_left.bmp";
		std::wstring rightPath = L"..\\Assets\\Arts\\Monsters\\Bats\\Bats_right.bmp";
		mLeftAnimation = L"Bat_Left";
		mRightAnimation = L"Bat_Right";
		mLeftShadowAnimation = L"Bat_Left_Shadow";
		mRightShadowAnimation = L"Bat_Right_Shadow";

		mAnimator->CreateAnimation(mLeftAnimation, mLeftAnimation, leftPath, 4, 8, 0, 2, 4, -Vector2(12, 24), BeatManager::SecondsPerBeat());
		mAnimator->CreateAnimation(mRightAnimation, mRightAnimation, rightPath, 4, 8, 0, 2, 4, -Vector2(12, 24), BeatManager::SecondsPerBeat());
		mAnimator->CreateAnimation(mLeftShadowAnimation, mLeftAnimation, leftPath, 4, 8, 0, 1, 4, -Vector2(12, 24), BeatManager::SecondsPerBeat());
		mAnimator->CreateAnimation(mRightShadowAnimation, mRightAnimation, rightPath, 4, 8, 0, 1, 4, -Vector2(12, 24), BeatManager::SecondsPerBeat());
		Turn(Vector2::Right);
	}
	void RedBatSprite::Turn(Vector2 dir)
	{
		if (dir == Vector2::Left || dir == Vector2::Right)
			mLookDir = dir;
		if (mLookDir == Vector2::Left)
		{
			if (!mbInShadows)
				mAnimator->Play(mLeftAnimation, Animator::PlaySetting::Loop, true);
			else
				mAnimator->Play(mLeftShadowAnimation, Animator::PlaySetting::Loop, true);
		}
		else if (mLookDir == Vector2::Right)
		{
			if (!mbInShadows)
				mAnimator->Play(mRightAnimation, Animator::PlaySetting::Loop, false);
			else
				mAnimator->Play(mRightShadowAnimation, Animator::PlaySetting::Loop, false);
		}
	}
}