#include "LKnightSprite.h"
#include "LAnimator.h"
namespace cl
{

	KnightSprite::KnightSprite(Scene* sc)
		: PiecesSprite(sc)
	{
	}

	void KnightSprite::Initialize()
	{
		PiecesSprite::Initialize();
		std::wstring path = L"..\\Assets\\Arts\\Boss\\Deep Blues\\Knight.bmp";
		mAnimator->CreateAnimation(mIdle, L"Knight", path, 4, 2, 0, 0, 4, -Vector2(92 * 0.25 * 0.5, 56 * 0.5f), BeatManager::SecondsPerBeat());
		mAnimator->CreateAnimation(mShadowIdle, L"Knight", path, 4, 2, 0, 1, 4, -Vector2(92 * 0.25 * 0.5, 56 * 0.5f), BeatManager::SecondsPerBeat());
		path = L"..\\Assets\\Arts\\Boss\\Deep Blues\\Knight_Ready.bmp";
		mAnimator->CreateAnimation(mReady, L"Knight_Ready", path, 1, 2, 0, 0, 1, -Vector2(9, 56 * 0.5), BeatManager::SecondsPerBeat());
		mAnimator->CreateAnimation(mShadowReady, L"Knight_Ready", path, 1, 2, 0, 1, 1, -Vector2(9, 56 * 0.5), BeatManager::SecondsPerBeat());
		Idle();
	}
}