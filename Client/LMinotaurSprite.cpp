#include "LMinotaurSprite.h"
#include "LAnimator.h"
namespace cl
{
	MinotaurSprite::MinotaurSprite(Scene* sc)
		:CharacterSprite(sc)
		, mMinoState(MinotaurBase::State::Idle)
	{
		mAnimations[0][0] = L"IdleRight";
		mAnimations[0][1] = L"IdleLeft";
		mAnimations[1][0] = L"ChargeRight";
		mAnimations[1][1] = L"ChargeLeft";
		mAnimations[2][0] = L"FaintRight";
		mAnimations[2][1] = L"FaintLeft";

		mShadowAnimations[0][0] = L"ShadowIdleRight";
		mShadowAnimations[0][1] = L"ShadowIdleLeft";
		mShadowAnimations[1][0] = L"ShadowChargeRight";
		mShadowAnimations[1][1] = L"ShadowChargeLeft";
		mShadowAnimations[2][0] = L"ShadowFaintRight";
		mShadowAnimations[2][1] = L"ShadowFaintLeft";
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
			return 0;
		else
			return 1;
	}
	void MinotaurSprite::PlayAnimation()
	{
		if (mbInShadows)
			mAnimator->Play(mShadowAnimations[(int)mMinoState][GetIndex(mLookDir)], true, mLookDir == Vector2::Right);
		else
			mAnimator->Play(mAnimations[(int)mMinoState][GetIndex(mLookDir)], true, mLookDir == Vector2::Right);
	}
}