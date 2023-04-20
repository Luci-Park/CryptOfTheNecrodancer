#include "LGreenSlimeSprite.h"
#include "LAnimator.h"
namespace cl
{
	GreenSlimeSprite::GreenSlimeSprite(Scene* sc)
		: CharacterSprite(sc)
	{
	}
	GreenSlimeSprite::~GreenSlimeSprite()
	{
	}
	void GreenSlimeSprite::Initialize()
	{
		CharacterSprite::Initialize();
		mAnimator = AddComponent<Animator>();

		std::wstring leftPath = L"..\\Assets\\Arts\\Monsters\\Slimes\\Slimes_Left.bmp";
		std::wstring rightPath = L"..\\Assets\\Arts\\Monsters\\Slimes\\Slimes_Right.bmp";

		mAnimator->CreateAnimation(L"LeftIdle", L"Slime_Left", leftPath, 4, 8, 0, 4, 4, -Vector2(13, 22), BeatManager::BeatDuration());
		mAnimator->CreateAnimation(L"RightIdle", L"Slime_Right", rightPath, 4, 8, 0, 4, 4, -Vector2(13, 22), BeatManager::BeatDuration());
		mAnimator->CreateAnimation(L"LeftIdleShadow", L"Slime_Left", leftPath, 4, 8, 0, 5, 4, -Vector2(13, 22), BeatManager::BeatDuration());
		mAnimator->CreateAnimation(L"RightIdleShadow", L"Slime_Right", rightPath, 4, 8, 0, 5, 4, -Vector2(13, 22), BeatManager::BeatDuration());

		Turn(GetRandomInt(0, 1) ? Vector2::Left : Vector2::Right);
		Idle();
	}
	void GreenSlimeSprite::Update()
	{
		CharacterSprite::Update();
	}
	void GreenSlimeSprite::Render(HDC hdc)
	{
		CharacterSprite::Render(hdc);
	}
	void GreenSlimeSprite::Turn(Vector2 dir)
	{
		if (dir == Vector2::Left || dir == Vector2::Right)
			mLookDir = dir;
		Idle();
	}
	void GreenSlimeSprite::OnBeatChanged()
	{
		mAnimator->SetDuration(BeatManager::BeatDuration());
	}
	void GreenSlimeSprite::Idle()
	{
		if (mLookDir == Vector2::Left)
		{
			if (mbInShadows)
				mAnimator->Play(L"LeftIdleShadow", true, false);
			else
				mAnimator->Play(L"LeftIdle", true, false);
		}
		else
		{
			if (mbInShadows)
				mAnimator->Play(L"RightIdleShadow", true, false);
			else
				mAnimator->Play(L"RightIdle", true, false);
		}
	}
}