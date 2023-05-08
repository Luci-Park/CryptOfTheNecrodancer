#include "LRedDragonSprite.h"
#include "LAnimator.h"
namespace cl
{
	RedDragonSprite::RedDragonSprite(Scene* sc)
		: CharacterSprite(sc)
		, mDragonState(DragonBase::State::Idle)
	{
		mAnimations[0][1] = L"IdleRight";
		mAnimations[0][0] = L"IdleLeft";
		mAnimations[1][1] = L"ReadyFireRight";
		mAnimations[1][0] = L"ReadyFireLeft";
		mAnimations[2][1] = L"FireRight";
		mAnimations[2][0] = L"FireLeft";

		mShadowAnimations[0][1] = L"ShadowIdleRight";
		mShadowAnimations[0][0] = L"ShadowIdleLeft";
		mShadowAnimations[1][1] = L"ShadowReadyFireRight";
		mShadowAnimations[1][0] = L"ShadowReadyFireLeft";
		mShadowAnimations[2][1] = L"ShadowFireRight";
		mShadowAnimations[2][0] = L"ShadowFireLeft";
	}
	RedDragonSprite::~RedDragonSprite()
	{
	}
	void RedDragonSprite::SetDragonState(DragonBase::State state)
	{
		mDragonState = state;
	}
	void RedDragonSprite::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		CharacterSprite::Initialize();
		std::wstring path = L"..\\Assets\\Arts\\Miniboss\\Dragon\\RedDragon.bmp";
		mAnimator->CreateAnimation(mAnimations[0][0], L"RedDragon", path, 18, 2, 0, 0, 4, Vector2(-30, -51), BeatManager::SecondsPerBeat());
		mAnimator->CreateAnimation(mAnimations[1][0], L"RedDragon", path, 18, 2, 4, 0, 3, Vector2(-30, -51), BeatManager::SecondsPerBeat());
		mAnimator->CreateAnimation(mAnimations[2][0], L"RedDragon", path, 18, 2, 7, 0, 2, Vector2(-30, -51), BeatManager::SecondsPerBeat());
		mAnimator->CreateAnimation(mAnimations[2][1], L"RedDragon", path, 18, 2, 9, 0, 2, Vector2(-30, -51), BeatManager::SecondsPerBeat());
		mAnimator->CreateAnimation(mAnimations[1][1], L"RedDragon", path, 18, 2, 11, 0, 3, Vector2(-30, -51), BeatManager::SecondsPerBeat());
		mAnimator->CreateAnimation(mAnimations[0][1], L"RedDragon", path, 18, 2, 14, 0, 4, Vector2(-30, -51), BeatManager::SecondsPerBeat());


		mAnimator->CreateAnimation(mShadowAnimations[0][0], L"RedDragon", path, 18, 2, 0, 1, 4, Vector2(-30, -51), BeatManager::SecondsPerBeat());
		mAnimator->CreateAnimation(mShadowAnimations[1][0], L"RedDragon", path, 18, 2, 4, 1, 3, Vector2(-30, -51), BeatManager::SecondsPerBeat());
		mAnimator->CreateAnimation(mShadowAnimations[2][0], L"RedDragon", path, 18, 2, 7, 1, 2, Vector2(-30, -51), BeatManager::SecondsPerBeat());
		mAnimator->CreateAnimation(mShadowAnimations[2][1], L"RedDragon", path, 18, 2, 9, 1, 2, Vector2(-30, -51), BeatManager::SecondsPerBeat());
		mAnimator->CreateAnimation(mShadowAnimations[1][1], L"RedDragon", path, 18, 2, 11, 1, 3, Vector2(-30, -51), BeatManager::SecondsPerBeat());
		mAnimator->CreateAnimation(mShadowAnimations[0][1], L"RedDragon", path, 18, 2, 14, 1, 4, Vector2(-30, -51), BeatManager::SecondsPerBeat());
	}
	void RedDragonSprite::Turn(Vector2 dir)
	{
		if (dir == Vector2::Left || Vector2::Right == dir)
			mLookDir = dir;
		PlayAnimation();
	}
	int RedDragonSprite::GetIndex(Vector2 dir)
	{
		if (dir == Vector2::Right)
			return 1;
		else
			return 0;
	}
	void RedDragonSprite::PlayAnimation()
	{
		auto settings = mDragonState == DragonBase::State::Idle ? Animator::PlaySetting::Loop : Animator::PlaySetting::PauseAtEnd;
		if (mbInShadows)
			mAnimator->Play(mShadowAnimations[(int)mDragonState][GetIndex(mLookDir)], settings, mLookDir == Vector2::Right);
		else
			mAnimator->Play(mAnimations[(int)mDragonState][GetIndex(mLookDir)], settings, mLookDir == Vector2::Right);
	}
}
