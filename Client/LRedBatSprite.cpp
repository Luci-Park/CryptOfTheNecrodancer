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

		mAnimator->CreateAnimation(mLeftAnimation, mLeftAnimation, leftPath, 4, 8, 0, 2, 4, -Vector2(12, 24), 0.36f);
		mAnimator->CreateAnimation(mRightAnimation, mRightAnimation, rightPath, 4, 8, 0, 2, 4, -Vector2(12, 24), 0.36f);
		mAnimator->CreateAnimation(mLeftShadowAnimation, mLeftAnimation, leftPath, 4, 8, 0, 1, 4, -Vector2(12, 24), 0.36f);
		mAnimator->CreateAnimation(mRightShadowAnimation, mRightAnimation, rightPath, 4, 8, 0, 1, 4, -Vector2(12, 24), 0.36f);
		Turn(Vector2::Right);
	}
	void RedBatSprite::Turn(Vector2 dir)
	{
		if (dir == Vector2::Left)
		{
			if (mbIsRevealed)
				mAnimator->PlayNoDuplication(mLeftAnimation, true, true);
			else
				mAnimator->PlayNoDuplication(mLeftShadowAnimation, true, true);
		}
		else if (dir == Vector2::Right)
		{
			if (mbIsRevealed)
				mAnimator->PlayNoDuplication(mRightAnimation, true, false);
			else
				mAnimator->PlayNoDuplication(mRightShadowAnimation, true, false);
		}
	}
}