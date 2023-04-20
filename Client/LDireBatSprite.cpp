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
	void DireBatSprite::SetY(int y)
	{
		std::wstring leftPath = L"..\\Assets\\Arts\\Miniboss\\DireBat_left.bmp";
		std::wstring rightPath = L"..\\Assets\\Arts\\Monsters\\Bats\\DireBat_right.bmp";
		mLeftAnimation = L"Dire_Left";
		mRightAnimation = L"Dire_Right";
		mLeftShadowAnimation = L"Dire_Left_Shadow";
		mRightShadowAnimation = L"Dire_Right_Shadow";

		mAnimator->CreateAnimation(mLeftAnimation, mLeftAnimation, leftPath, 4, 8, 0, y, 4, -Vector2(12, 24), BeatManager::BeatDuration());
		mAnimator->CreateAnimation(mRightAnimation, mRightAnimation, rightPath, 4, 8, 0, y, 4, -Vector2(12, 24), BeatManager::BeatDuration());

		mAnimator->CreateAnimation(mLeftShadowAnimation, mLeftAnimation, leftPath, 4, 8, 0, y + 1, 4, -Vector2(12, 24), BeatManager::BeatDuration());
		mAnimator->CreateAnimation(mRightShadowAnimation, mRightAnimation, rightPath, 4, 8, 0, y + 1, 4, -Vector2(12, 24), BeatManager::BeatDuration());
		Turn(Vector2::Right);
	}
}