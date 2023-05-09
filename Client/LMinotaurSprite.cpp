#include "LMinotaurSprite.h"
#include "LAnimator.h"
namespace cl
{
	MinotaurSprite::MinotaurSprite(Scene* sc)
		:CharacterSprite(sc)
		, mMinoState(MinotaurBase::State::Idle)
	{
		mAnimations[0][1] = L"IdleRight";
		mAnimations[0][0] = L"IdleLeft";
		mAnimations[1][1] = L"ChargeRight";
		mAnimations[1][0] = L"ChargeLeft";
		mAnimations[2][1] = L"FaintRight";
		mAnimations[2][0] = L"FaintLeft";

		mShadowAnimations[0][1] = L"ShadowIdleRight";
		mShadowAnimations[0][0] = L"ShadowIdleLeft";
		mShadowAnimations[1][1] = L"ShadowChargeRight";
		mShadowAnimations[1][0] = L"ShadowChargeLeft";
		mShadowAnimations[2][1] = L"ShadowFaintRight";
		mShadowAnimations[2][0] = L"ShadowFaintLeft";
	}
	MinotaurSprite::~MinotaurSprite()
	{
	}
	void MinotaurSprite::SetMinoState(MinotaurBase::State state)
	{
		mMinoState = state;
	}
	void MinotaurSprite::SetY(int y)
	{
		std::wstring path = L"..\\Assets\\Arts\\Miniboss\\Minotaurs\\";
		mAnimator->CreateAnimation(mAnimations[0][0], L"MinotaursIdle", path + L"MinotaursIdle.bmp", 8, 4, 0, y * 2, 4, Vector2(-25, -49), Conductor::Instance().SecondsPerBeat());
		mAnimator->CreateAnimation(mAnimations[0][1], L"MinotaursIdle", path + L"MinotaursIdle.bmp", 8, 4, 4, y * 2, 4, Vector2(-25, -49), Conductor::Instance().SecondsPerBeat());
		mAnimator->CreateAnimation(mShadowAnimations[0][0], L"MinotaursIdle", path + L"MinotaursIdle.bmp", 8, 4, 0, y * 2 + 1, 4, Vector2(-25, -49), Conductor::Instance().SecondsPerBeat());
		mAnimator->CreateAnimation(mShadowAnimations[0][1], L"MinotaursIdle", path + L"MinotaursIdle.bmp", 8, 4, 4, y * 2 + 1, 4, Vector2(-25, -49), Conductor::Instance().SecondsPerBeat());

		mAnimator->CreateAnimation(mAnimations[1][0], L"MinotaursCharge", path + L"MinotaursCharge.bmp", 2, 4, 0, y * 2, 1, Vector2(-21, -49), Conductor::Instance().SecondsPerBeat());
		mAnimator->CreateAnimation(mAnimations[1][1], L"MinotaursCharge", path + L"MinotaursCharge.bmp", 2, 4, 1, y * 2, 1, Vector2(-21, -49), Conductor::Instance().SecondsPerBeat());
		mAnimator->CreateAnimation(mShadowAnimations[1][0], L"MinotaursCharge", path + L"MinotaursCharge.bmp", 2, 4, 0, y * 2 + 1, 1, Vector2(-21, -49), Conductor::Instance().SecondsPerBeat());
		mAnimator->CreateAnimation(mShadowAnimations[1][1], L"MinotaursCharge", path + L"MinotaursCharge.bmp", 2, 4, 1, y * 2 + 1, 1, Vector2(-21, -49), Conductor::Instance().SecondsPerBeat());

		mAnimator->CreateAnimation(mAnimations[2][0], L"MinotaursFaint", path + L"MinotaursFaint.bmp", 8, 4, 0, y * 2, 4, Vector2(-25, -49), Conductor::Instance().SecondsPerBeat());
		mAnimator->CreateAnimation(mAnimations[2][1], L"MinotaursFaint", path + L"MinotaursFaint.bmp", 8, 4, 4, y * 2, 4, Vector2(-25, -49), Conductor::Instance().SecondsPerBeat());
		mAnimator->CreateAnimation(mShadowAnimations[2][0], L"MinotaursFaint", path + L"MinotaursFaint.bmp", 8, 4, 0, y * 2 + 1, 4, Vector2(-25, -49), Conductor::Instance().SecondsPerBeat());
		mAnimator->CreateAnimation(mShadowAnimations[2][1], L"MinotaursFaint", path + L"MinotaursFaint.bmp", 8, 4, 4, y * 2 + 1, 4, Vector2(-25, -49), Conductor::Instance().SecondsPerBeat());
	}
	void MinotaurSprite::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		CharacterSprite::Initialize();
	}
	void MinotaurSprite::Turn(Vector2 dir)
	{
		if (dir == Vector2::Right || dir == Vector2::Left)
			mLookDir = dir;
		PlayAnimation();
	}
	int MinotaurSprite::GetIndex(Vector2 dir)
	{
		if (dir == Vector2::Right)
			return 1;
		else
			return 0;
	}
	void MinotaurSprite::PlayAnimation()
	{
		if (mbInShadows)
			mAnimator->Play(mShadowAnimations[(int)mMinoState][GetIndex(mLookDir)],Animator::PlaySetting::Loop, mLookDir == Vector2::Right);
		else
			mAnimator->Play(mAnimations[(int)mMinoState][GetIndex(mLookDir)], Animator::PlaySetting::Loop, mLookDir == Vector2::Right);
	}
}