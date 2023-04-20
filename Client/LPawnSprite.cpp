#include "LPawnSprite.h"
#include "LAnimator.h"
namespace cl
{
	PawnSprite::PawnSprite(Scene* sc)
		:CharacterSprite(sc)
	{
	}
	void PawnSprite::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		CharacterSprite::Initialize();
		mIdle = L"Idle";
		mReady = L"Ready";
		std::wstring path = L"..\\Assets\\Arts\\Boss\\Deep Blues\\Pawn.bmp";
		mAnimator->CreateAnimation(mIdle, L"Pawn", path, 4, 2, 0, 0, 4, -Vector2(60 * 0.25 * 0.5, 46 * 0.5f), BeatManager::BeatDuration());
		path = L"..\\Assets\\Arts\\Boss\\Deep Blues\\Pawn_Ready.bmp";
		mAnimator->CreateAnimation(mReady, L"Pawn_Ready", path, 1, 2, 0, 0, 1, -Vector2(15 * 0.5f, 45 * 0.5), BeatManager::BeatDuration());
		Idle();
	}
	void PawnSprite::Ready()
	{
		if (!mAnimator->IsAnimationPlaying(mReady))
			mAnimator->Play(mReady, true, false);
	}
	void PawnSprite::Idle()
	{
		if (!mAnimator->IsAnimationPlaying(mIdle))
			mAnimator->Play(mIdle, true, false);
	}
}