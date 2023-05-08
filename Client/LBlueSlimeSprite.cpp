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

		mAnimator->CreateAnimation(L"LeftIdle", L"Slime_Left", leftPath, 4, 8, 0, 0, 4, -Vector2(13, 22), BeatManager::SecondsPerBeat());
		mAnimator->CreateAnimation(L"LeftJump", L"Slime_Left", leftPath, 4, 8, 0, 2, 4, -Vector2(13, 22), BeatManager::SecondsPerBeat());
		mAnimator->CreateAnimation(L"RightIdle", L"Slime_Right", rightPath, 4, 8, 0, 0, 4, -Vector2(13, 22), BeatManager::SecondsPerBeat());
		mAnimator->CreateAnimation(L"RightJump", L"Slime_Right", rightPath, 4, 8, 0, 2, 4, -Vector2(13, 22), BeatManager::SecondsPerBeat());
		mAnimator->CreateAnimation(L"LeftIdleShadow", L"Slime_Left", leftPath, 4, 8, 0, 1, 4, -Vector2(13, 22), BeatManager::SecondsPerBeat());
		mAnimator->CreateAnimation(L"LeftJumpShadow", L"Slime_Left", leftPath, 4, 8, 0, 3, 4, -Vector2(13, 22), BeatManager::SecondsPerBeat());
		mAnimator->CreateAnimation(L"RightIdleShadow", L"Slime_Right", rightPath, 4, 8, 0, 1, 4, -Vector2(13, 22), BeatManager::SecondsPerBeat());
		mAnimator->CreateAnimation(L"RightJumpShadow", L"Slime_Right", rightPath, 4, 8, 0, 3, 4, -Vector2(13, 22), BeatManager::SecondsPerBeat());

		Turn(GetRandomInt(0, 1) ? Vector2::Left : Vector2::Right);
		Idle();
	}
	void BlueSlimeSprite::Update()
	{
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
		if (mbIsJumping)
			JumpAnimation();
		else
			Idle();
	}
	void BlueSlimeSprite::OnBeatChanged()
	{
		mAnimator->SetDuration(BeatManager::SecondsPerBeat());
	}
	void BlueSlimeSprite::Idle()
	{
		if (mLookDir == Vector2::Left)
		{
			if (mbInShadows)
				mAnimator->Play(L"LeftIdleShadow", Animator::PlaySetting::Loop, false);
			else
				mAnimator->Play(L"LeftIdle", Animator::PlaySetting::Loop, false);
		}
		else
		{
			if (mbInShadows)
				mAnimator->Play(L"RightIdleShadow", Animator::PlaySetting::Loop, false);
			else
				mAnimator->Play(L"RightIdle", Animator::PlaySetting::Loop, false);
		}
	}
	void BlueSlimeSprite::JumpAnimation()
	{
		if (mLookDir == Vector2::Left)
		{
			if (mbInShadows)
				mAnimator->Play(L"LeftJumpShadow", Animator::PlaySetting::Loop, false);
			else
				mAnimator->Play(L"LeftJump", Animator::PlaySetting::Loop, false);
		}
		else
		{
			if (mbInShadows)
				mAnimator->Play(L"RightJumpShadow", Animator::PlaySetting::Loop, false);
			else
				mAnimator->Play(L"RightJump", Animator::PlaySetting::Loop, false);
		}
	}
}