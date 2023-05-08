#include "LRookSprite.h"
#include "LAnimator.h"
namespace cl
{
	RookSprite::RookSprite(Scene* sc)
		: PiecesSprite(sc)
	{
	}

	void RookSprite::Initialize()
	{
		PiecesSprite::Initialize();
		std::wstring path = L"..\\Assets\\Arts\\Boss\\Deep Blues\\Rook.bmp";
		mAnimator->CreateAnimation(mIdle, L"Rook", path, 2, 2, 0, 0, 2, -Vector2(38 * 0.25, 52 * 0.5f), BeatManager::SecondsPerBeat());
		mAnimator->CreateAnimation(mShadowIdle, L"Rook", path, 2, 2, 0, 1, 2, -Vector2(38 * 0.25, 52 * 0.5f), BeatManager::SecondsPerBeat());
		path = L"..\\Assets\\Arts\\Boss\\Deep Blues\\Rook_Ready.bmp";
		mAnimator->CreateAnimation(mReady, L"Rook_Ready", path, 1, 2, 0, 0, 1, -Vector2(9, 52 * 0.5), BeatManager::SecondsPerBeat());
		mAnimator->CreateAnimation(mShadowReady, L"Rook_Ready", path, 1, 2, 0, 1, 1, -Vector2(9, 52 * 0.5), BeatManager::SecondsPerBeat());
		Idle();
	}

}