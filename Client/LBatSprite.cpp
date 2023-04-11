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
		leftAnimation = L"Bat_Left";
		rightAnimation = L"Bat_Right";

		mAnimator->CreateAnimation(leftAnimation, leftAnimation, leftPath, 4, 8, 0, 0, 4, Vector2::Zero, 0.36f);
		mAnimator->CreateAnimation(rightAnimation, rightAnimation, rightPath, 4, 8, 0, 0, 4, Vector2::Zero, 0.36f);
		Turn(Vector2::Right);
	}
	void BatSprite::Turn(Vector2 dir)
	{
		if (dir == Vector2::Left)
		{
			if (!mAnimator->IsAnimationPlaying(leftAnimation))
				mAnimator->Play(leftAnimation, true, true);
		}
		else if (dir == Vector2::Right)
		{
			if (!mAnimator->IsAnimationPlaying(rightAnimation))
				mAnimator->Play(rightAnimation, true, false);
		}
	}
}