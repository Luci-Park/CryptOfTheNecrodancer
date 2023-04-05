#include "LOrangeSlimeSprite.h"
#include "LBeatManager.h"
#include "LAnimator.h"
#include "LCamera.h"
namespace cl
{
	OrangeSlimeSprite::OrangeSlimeSprite(Scene* sc)
		: CharacterSprite(sc)
		, mAnimator(nullptr)
	{
	}
	OrangeSlimeSprite::~OrangeSlimeSprite()
	{
	}
	void OrangeSlimeSprite::Initialize()
	{
		CharacterSprite::Initialize();
		mAnimator = AddComponent<Animator>();

		std::wstring leftPath = L"..\\Assets\\Arts\\Monsters\\Slimes\\Slimes_Left.bmp";
		std::wstring rightPath = L"..\\Assets\\Arts\\Monsters\\Slimes\\Slimes_Right.bmp";

		mAnimator->CreateAnimation(L"LeftJump", L"Slime_Left", leftPath, 8, 16, 0, 4, 4, Vector2::Zero, 0.36f);
		mAnimator->CreateAnimation(L"RightJump", L"Slime_Right", rightPath, 8, 16, 4, 4, 4, Vector2::Zero, 0.36f);
		Turn(GetRandomInt(0, 1) ? Vector2::Left : Vector2::Right);
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
	}
	void OrangeSlimeSprite::OnBeatChanged()
	{
		mAnimator->SetDuration(BeatManager::BeatDuration());
	}
	void OrangeSlimeSprite::Jump()
	{
		CharacterSprite::Jump();
		if (mLookDir == Vector2::Left)
			mAnimator->Play(L"LeftJump", true, false);
		else
			mAnimator->Play(L"RightJump", true, true);
	}
}