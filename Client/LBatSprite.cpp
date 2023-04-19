#include "LBatSprite.h"
#include "LAnimator.h"
namespace cl
{
	BatSprite::BatSprite(Scene* sc)
		:CharacterSprite(sc)
	{
	}
	void BatSprite::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		CharacterSprite::Initialize();

		std::wstring leftPath = L"..\\Assets\\Arts\\Monsters\\Bats\\Bats_left.bmp";
		std::wstring rightPath = L"..\\Assets\\Arts\\Monsters\\Bats\\Bats_right.bmp";
		mLeftAnimation = L"Bat_Left";
		mRightAnimation = L"Bat_Right";
		mLeftShadowAnimation = L"Bat_Left_Shadow";
		mRightShadowAnimation = L"Bat_Right_Shadow";

		mAnimator->CreateAnimation(mLeftAnimation, mLeftAnimation, leftPath, 4, 8, 0, 0, 4, -Vector2(12, 24), 0.36f);
		mAnimator->CreateAnimation(mRightAnimation, mRightAnimation, rightPath, 4, 8, 0, 0, 4, -Vector2(12, 24), 0.36f);

		mAnimator->CreateAnimation(mLeftShadowAnimation, mLeftAnimation, leftPath, 4, 8, 0, 1, 4, -Vector2(12, 24), 0.36f);
		mAnimator->CreateAnimation(mRightShadowAnimation, mRightAnimation, rightPath, 4, 8, 0, 1, 4, -Vector2(12, 24), 0.36f);
		Turn(Vector2::Right);
	}
	void BatSprite::Turn(Vector2 dir)
	{
		if (dir == Vector2::Left || dir == Vector2::Right)
			mLookDir = dir;
		if (mLookDir == Vector2::Left)
		{
			if (!mbInShadows)
				mAnimator->Play(mLeftAnimation, true, true);
			else
				mAnimator->Play(mLeftShadowAnimation, true, true);
		}
		else if (mLookDir == Vector2::Right)
		{
			if (!mbInShadows)
				mAnimator->Play(mRightAnimation, true, false);
			else
				mAnimator->Play(mRightShadowAnimation, true, false);
		}
	}
	void BatSprite::PlayAnimation()
	{
		Turn(mLookDir);
	}
}