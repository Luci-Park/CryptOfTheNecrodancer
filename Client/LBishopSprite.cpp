#include "LBishopSprite.h"
#include "LAnimator.h"
namespace cl
{
	BishopSprite::BishopSprite(Scene* sc)
		: CharacterSprite(sc)
		, mState(State::Idle)
	{
	}

	void BishopSprite::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		CharacterSprite::Initialize();
		mIdle = L"Idle";
		mReady = L"Ready";
		mShadowIdle = L"ShadowIdle";
		mShadowReady = L"ShadowReady";
		std::wstring path = L"..\\Assets\\Arts\\Boss\\Deep Blues\\Bishop.bmp";
		mAnimator->CreateAnimation(mIdle, L"Bishop", path, 4, 2, 0, 0, 4, -Vector2(13 * 0.5, 32), BeatManager::BeatDuration() * 2);
		mAnimator->CreateAnimation(mShadowIdle, L"Bishop", path, 4, 2, 0, 1, 4, -Vector2(13 * 0.5, 32), BeatManager::BeatDuration() * 2);
		path = L"..\\Assets\\Arts\\Boss\\Deep Blues\\Bishop_Ready.bmp";
		mAnimator->CreateAnimation(mReady, L"Bishop_Ready", path, 1, 2, 0, 0, 1, -Vector2(17 *0.5, 32), BeatManager::BeatDuration());
		mAnimator->CreateAnimation(mShadowReady, L"Bishop_Ready", path, 1, 2, 0, 1, 1, -Vector2(17 *0.5, 32), BeatManager::BeatDuration());
	}

	void BishopSprite::Turn(Vector2 dir)
	{
		if (mState == State::Idle)
			Idle();
		else
			Ready();
	}

	void BishopSprite::OnBeatChanged()
	{
		mAnimator->SetDuration(BeatManager::BeatDuration() * 2);
	}

	void BishopSprite::Ready()
	{
		if (mbInShadows)
			mAnimator->Play(mShadowReady, Animator::PlaySetting::Loop, false);
		else
			mAnimator->Play(mReady, Animator::PlaySetting::Loop, false);
		mState = State::Ready;
	}

	void BishopSprite::Idle()
	{
		if (mbInShadows)
			mAnimator->Play(mShadowIdle, Animator::PlaySetting::Loop, false);
		else
			mAnimator->Play(mIdle, Animator::PlaySetting::Loop, false);
		mState = State::Idle;
	}

}
