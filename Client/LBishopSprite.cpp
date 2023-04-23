#include "LBishopSprite.h"
#include "LAnimator.h"
namespace cl
{
	BishopSprite::BishopSprite(Scene* sc)
		: CharacterSprite(sc)
	{
	}

	void BishopSprite::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		CharacterSprite::Initialize();
		mIdle = L"Idle";
		mReady = L"Ready";
		std::wstring path = L"..\\Assets\\Arts\\Boss\\Deep Blues\\Bishop.bmp";
		mAnimator->CreateAnimation(mIdle, L"Bishop", path, 4, 2, 0, 0, 4, -Vector2(13 * 0.5, 32), BeatManager::BeatDuration());
		path = L"..\\Assets\\Arts\\Boss\\Deep Blues\\Bishop_Ready.bmp";
		mAnimator->CreateAnimation(mReady, L"Bishop_Ready", path, 1, 2, 0, 0, 1, -Vector2(17 *0.5, 32), BeatManager::BeatDuration());
		Idle();
	}

	void BishopSprite::Ready()
	{
		if (!mAnimator->IsAnimationPlaying(mReady))
			mAnimator->Play(mReady, Animator::PlaySetting::Loop, false);
	}

	void BishopSprite::Idle()
	{
		if (!mAnimator->IsAnimationPlaying(mIdle))
			mAnimator->Play(mIdle, Animator::PlaySetting::Loop, false);
	}

}
