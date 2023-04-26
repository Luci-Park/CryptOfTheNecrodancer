#include "LQueenSprite.h"
#include "LAnimator.h"
namespace cl
{
	QueenSprite::QueenSprite(Scene* sc)
		:PiecesSprite(sc)
	{
	}
	void QueenSprite::Initialize()
	{
		PiecesSprite::Initialize();
		std::wstring path = L"..\\Assets\\Arts\\Boss\\Deep Blues\\Queen.bmp";
		mAnimator->CreateAnimation(mIdle, L"Queen", path, 1, 2, 0, 0, 1, -Vector2(33 * 0.5f, 78 * 0.5f), BeatManager::BeatDuration() * 2);
		mAnimator->CreateAnimation(mShadowIdle, L"Queen", path, 1, 2, 0, 1, 1, -Vector2(33 * 0.5f, 78 * 0.5f), BeatManager::BeatDuration() * 2);
		mReady = mIdle;
		mShadowReady = mShadowIdle;
		Idle();
	}
}