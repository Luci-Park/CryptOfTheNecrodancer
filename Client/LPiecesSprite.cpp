#include "LPiecesSprite.h"
#include "LAnimator.h"
namespace cl
{
	PiecesSprite::PiecesSprite(Scene* sc)
		: CharacterSprite(sc)
		, mState(PiecesSprite::State::Idle)
	{
		mAnimator = AddComponent<Animator>();
	}
	void PiecesSprite::Initialize()
	{
		CharacterSprite::Initialize();
		mIdle = L"Idle";
		mReady = L"Ready";
		mShadowIdle = L"ShadowIdle";
		mShadowReady = L"ShadowReady";
	}
	void PiecesSprite::Turn(Vector2 dir)
	{
		if (mState == State::Idle)
			Idle();
		else
			Ready();
	}
	void PiecesSprite::OnBeatChanged()
	{
		mAnimator->SetDuration(BeatManager::BeatDuration() * 2);
	}
	void PiecesSprite::Ready()
	{
		if (mbInShadows)
			mAnimator->Play(mShadowReady, Animator::PlaySetting::Loop, false);
		else
			mAnimator->Play(mReady, Animator::PlaySetting::Loop, false);
		mState = State::Ready;
	}
	void PiecesSprite::Idle()
	{
		if (mbInShadows)
			mAnimator->Play(mShadowIdle, Animator::PlaySetting::Loop, false);
		else
			mAnimator->Play(mIdle, Animator::PlaySetting::Loop, false);
		mState = State::Idle;
	}
}