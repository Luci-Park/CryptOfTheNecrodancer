#include "LDirebatSprite.h"
#include "LAnimator.h"
namespace cl
{
	DireBatSprite::DireBatSprite(Scene* sc)
		:CharacterSprite(sc)
	{
	}
	DireBatSprite::~DireBatSprite()
	{
	}
	void DireBatSprite::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		CharacterSprite::Initialize();
	}
	void DireBatSprite::Turn(Vector2 dir)
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
	void DireBatSprite::SetY(int y)
	{
		std::wstring path = L"..\\Assets\\Arts\\Miniboss\\Dire Bats.bmp";
		mLeftAnimation = L"Dire_Left";
		mRightAnimation = L"Dire_Right";
		mLeftShadowAnimation = L"Dire_Left_Shadow";
		mRightShadowAnimation = L"Dire_Right_Shadow";

		mAnimator->CreateAnimation(mRightAnimation, L"DireBat", path, 8, 4, 0, y * 2, 4, -Vector2(12, 24), Conductor::Instance().SecondsPerBeat());
		mAnimator->CreateAnimation(mLeftAnimation, L"DireBat", path, 8, 4, 4, y * 2, 4, -Vector2(12, 24), Conductor::Instance().SecondsPerBeat());

		mAnimator->CreateAnimation(mRightShadowAnimation, L"DireBat", path, 8, 4, 0, y * 2 + 1, 4, -Vector2(12, 24), Conductor::Instance().SecondsPerBeat());
		mAnimator->CreateAnimation(mLeftShadowAnimation, L"DireBat", path, 8, 4, 4, y * 2 + 1, 4, -Vector2(12, 24), Conductor::Instance().SecondsPerBeat());
		Turn(Vector2::Right);
	}
}