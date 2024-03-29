#include "LOrangeSlimeSprite.h"
#include "LConductor.h"
#include "LAnimator.h"
#include "LCamera.h"
namespace cl
{
	OrangeSlimeSprite::OrangeSlimeSprite(Scene* sc)
		: CharacterSprite(sc)
	{
	}
	OrangeSlimeSprite::~OrangeSlimeSprite()
	{
	}
	void OrangeSlimeSprite::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		CharacterSprite::Initialize();

		std::wstring leftPath = L"..\\Assets\\Arts\\Monsters\\Slimes\\Slimes_Left.bmp";
		std::wstring rightPath = L"..\\Assets\\Arts\\Monsters\\Slimes\\Slimes_Right.bmp";

		mAnimator->CreateAnimation(L"LeftJump", L"Slime_Left", leftPath, 4, 8, 0, 6, 4, -Vector2(13, 22), Conductor::Instance().SecondsPerBeat());
		mAnimator->CreateAnimation(L"RightJump", L"Slime_Right", rightPath, 4, 8, 0, 6, 4, -Vector2(13, 22), Conductor::Instance().SecondsPerBeat());
		mAnimator->CreateAnimation(L"LeftJumpShadow", L"Slime_Left", leftPath, 4, 8, 0, 7, 4, -Vector2(13, 22), Conductor::Instance().SecondsPerBeat());
		mAnimator->CreateAnimation(L"RightJumpShadow", L"Slime_Right", rightPath, 4, 8, 0, 7, 4, -Vector2(13, 22), Conductor::Instance().SecondsPerBeat());
		mAnimator->Play(L"LeftJump", Animator::PlaySetting::Loop, false);
	}
	void OrangeSlimeSprite::Update()
	{
		CharacterSprite::Update();
	}
	void OrangeSlimeSprite::Render(HDC hdc)
	{
		CharacterSprite::Render(hdc);
	}
	void OrangeSlimeSprite::Turn(Vector2 dir)
	{
		if (dir == Vector2::Left || dir == Vector2::Right)
			mLookDir = dir;
		JumpAnimation();
	}
	void OrangeSlimeSprite::OnBeatChanged()
	{
		mAnimator->SetDuration(Conductor::Instance().SecondsPerBeat());
	}
	void OrangeSlimeSprite::JumpAnimation()
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