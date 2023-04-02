#include "LBlueSlimeSprite.h"
#include "LBeatManager.h"
#include "LAnimator.h"
namespace cl
{
	BlueSlimeSprite::BlueSlimeSprite(Scene* sc)
		: CharacterSprite(sc)
		, mAnimator(nullptr)
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

		mAnimator->CreateAnimation(L"LeftIdle", L"Slime_Left", leftPath, 8, 16, 0, 2, 4, Vector2::Zero, 0.36f);
		mAnimator->CreateAnimation(L"LeftJump", L"Slime_Left", leftPath, 8, 16, 4, 2, 4, Vector2::Zero, 0.36f);
		mAnimator->CreateAnimation(L"RightIdle", L"Slime_Right", rightPath, 8, 16, 4, 2, 4, Vector2::Zero, 0.36f);
		mAnimator->CreateAnimation(L"RightJump", L"Slime_Right", rightPath, 8, 16, 0, 2, 4, Vector2::Zero, 0.36f);

	}
	void BlueSlimeSprite::Update()
	{
	}
	void BlueSlimeSprite::Render(HDC hdc)
	{
	}
	void BlueSlimeSprite::Turn(Vector2 dir)
	{
		if (dir == Vector2::Left || dir == Vector2::Right)
			mLookDir = dir;
	}
	void BlueSlimeSprite::OnBeatChanged()
	{
		mAnimator->SetDuration(BeatManager::BeatDuration());
	}
	void BlueSlimeSprite::Idle()
	{
		if (mLookDir == Vector2::Left)
			mAnimator->Play(L"LeftIdle", false, false);
		else
			mAnimator->Play(L"RightIdle", false, true);
	}
	void BlueSlimeSprite::Jump()
	{
		CharacterSprite::Jump();
		if (mLookDir == Vector2::Left)
			mAnimator->Play(L"LeftJump", false, false);
		else
			mAnimator->Play(L"RightJump", false, true);
	}
}