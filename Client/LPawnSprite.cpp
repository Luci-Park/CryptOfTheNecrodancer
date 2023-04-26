#include "LPawnSprite.h"
#include "LAnimator.h"
namespace cl
{
	PawnSprite::PawnSprite(Scene* sc)
		:PiecesSprite(sc)
	{
	}
	void PawnSprite::Initialize()
	{
		PiecesSprite::Initialize();
		std::wstring path = L"..\\Assets\\Arts\\Boss\\Deep Blues\\Pawn.bmp";
		mAnimator->CreateAnimation(mIdle, L"Pawn", path, 4, 2, 0, 0, 4, -Vector2(60 * 0.25 * 0.5, 46 * 0.5f), BeatManager::BeatDuration());
		mAnimator->CreateAnimation(mShadowIdle, L"Pawn", path, 4, 2, 0, 1, 4, -Vector2(60 * 0.25 * 0.5, 46 * 0.5f), BeatManager::BeatDuration());
		path = L"..\\Assets\\Arts\\Boss\\Deep Blues\\Pawn_Ready.bmp";
		mAnimator->CreateAnimation(mReady, L"Pawn_Ready", path, 1, 2, 0, 0, 1, -Vector2(15 * 0.5f, 45 * 0.5), BeatManager::BeatDuration());
		mAnimator->CreateAnimation(mShadowReady, L"Pawn_Ready", path, 1, 2, 0, 1, 1, -Vector2(15 * 0.5f, 45 * 0.5), BeatManager::BeatDuration());
		Idle();
	}
}