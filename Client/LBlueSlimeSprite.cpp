#include "LBlueSlimeSprite.h"
#include "LAnimator.h"
namespace cl
{
	BlueSlimeSprite::BlueSlimeSprite(Scene* sc)
		: CharacterSprite(sc)
	{
	}
	BlueSlimeSprite::~BlueSlimeSprite()
	{
	}
	void BlueSlimeSprite::Initialize()
	{
		CharacterSprite::Initialize();
		mAnimator = AddComponent<Animator>();

		std::wstring leftPath = L"..\\Assets\\Arts\\Monsters\\Slimes\\Slimes_Left.bmp";
		std::wstring rightPath = L"..\\Assets\\Arts\\Monsters\\Slimes\\Slimes_Right.bmp";

		mAnimator->CreateAnimation(L"LeftIdle", L"Slime_Left", leftPath, 4, 8, 0, 0, 4, -Vector2(13, 22), BeatManager::BeatDuration());
		mAnimator->CreateAnimation(L"LeftJump", L"Slime_Left", leftPath, 4, 8, 0, 2, 4, -Vector2(13, 22), BeatManager::BeatDuration());
		mAnimator->CreateAnimation(L"RightIdle", L"Slime_Right", rightPath, 4, 8, 0, 0, 4, -Vector2(13, 22), BeatManager::BeatDuration());
		mAnimator->CreateAnimation(L"RightJump", L"Slime_Right", rightPath, 4, 8, 0, 2, 4, -Vector2(13, 22), BeatManager::BeatDuration());
		mAnimator->CreateAnimation(L"LeftIdleShadow", L"Slime_Left", leftPath, 4, 8, 0, 1, 4, -Vector2(13, 22), BeatManager::BeatDuration());
		mAnimator->CreateAnimation(L"LeftJumpShadow", L"Slime_Left", leftPath, 4, 8, 0, 3, 4, -Vector2(13, 22), BeatManager::BeatDuration());
		mAnimator->CreateAnimation(L"RightIdleShadow", L"Slime_Right", rightPath, 4, 8, 0, 1, 4, -Vector2(13, 22), BeatManager::BeatDuration());
		mAnimator->CreateAnimation(L"RightJumpShadow", L"Slime_Right", rightPath, 4, 8, 0, 3, 4, -Vector2(13, 22), BeatManager::BeatDuration());

		Turn(GetRandomInt(0, 1) ? Vector2::Left : Vector2::Right);
		Idle();
	}
	void BlueSlimeSprite::Update()
	{
		if (mbIsJumping)
			JumpAnimation();
		else
			Idle();
		CharacterSprite::Update();
	}
	void BlueSlimeSprite::Render(HDC hdc)
	{
		CharacterSprite::Render(hdc);
	}
	void BlueSlimeSprite::Turn(Vector2 dir)
	{
		if (dir == Vector2::Left || dir == Vector2::Right)
			mLookDir = dir;
		mAnimator->Reset();
	}
	void BlueSlimeSprite::OnBeatChanged()
	{
		mAnimator->SetDuration(BeatManager::BeatDuration());
	}
	void BlueSlimeSprite::Idle()
	{
		if (mLookDir == Vector2::Left)
		{
			if (mbInShadows)
				mAnimator->PlayNoDuplication(L"LeftIdleShadow", true, false);
			else
				mAnimator->PlayNoDuplication(L"LeftIdle", true, false);
		}
		else
		{
			if (mbInShadows)
				mAnimator->PlayNoDuplication(L"RightIdleShadow", true, false);
			else
				mAnimator->PlayNoDuplication(L"RightIdle", true, false);
		}
	}
	void BlueSlimeSprite::JumpAnimation()
	{
		if (mLookDir == Vector2::Left)
		{
			if (mbInShadows)
				mAnimator->PlayNoDuplication(L"LeftJumpShadow", true, false);
			else
				mAnimator->PlayNoDuplication(L"LeftJump", true, false);
		}
		else
		{
			if (mbInShadows)
				mAnimator->PlayNoDuplication(L"RightJumpShadow", true, false);
			else
				mAnimator->PlayNoDuplication(L"RightJump", true, false);
		}
	}
}