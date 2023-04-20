#include "LRookSprite.h"
#include "LAnimator.h"
namespace cl
{

	RookSprite::RookSprite(Scene* sc)
		: CharacterSprite(sc)
	{
	}

	void RookSprite::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		CharacterSprite::Initialize();
		mIdle = L"Idle";
		mReady = L"Ready";
		std::wstring path = L"..\\Assets\\Arts\\Boss\\Deep Blues\\Rook.bmp";
		mAnimator->CreateAnimation(mIdle, L"Rook", path, 2, 2, 0, 0, 2, -Vector2(38 * 0.25, 52 * 0.5f), BeatManager::BeatDuration());
		path = L"..\\Assets\\Arts\\Boss\\Deep Blues\\Rook_Ready.bmp";
		mAnimator->CreateAnimation(mReady, L"Rook_Ready", path, 1, 2, 0, 0, 1, -Vector2(9, 52 * 0.5), BeatManager::BeatDuration());
		Idle();
	}

	void RookSprite::Ready()
	{
		if (!mAnimator->IsAnimationPlaying(mReady))
			mAnimator->Play(mReady, true, false);
	}

	void RookSprite::Idle()
	{
		if (!mAnimator->IsAnimationPlaying(mIdle))
			mAnimator->Play(mIdle, true, false);
	}
}