#include "LKingSprite.h"
#include "LAnimator.h"
namespace cl
{
	KingSprite::KingSprite(Scene* sc)
		:PiecesSprite(sc)
	{
	}
	void KingSprite::Initialize()
	{
		PiecesSprite::Initialize();
		std::wstring path = L"..\\Assets\\Arts\\Boss\\Deep Blues\\King.bmp";
		mAnimator->CreateAnimation(mIdle, L"King", path, 4, 2, 0, 0, 4, -Vector2(13 * 0.5, 45), BeatManager::BeatDuration());
		mAnimator->CreateAnimation(mShadowIdle, L"King", path, 4, 2, 0, 1, 4, -Vector2(13 * 0.5, 45), BeatManager::BeatDuration());
		mReady = mIdle;
		mShadowReady = mShadowIdle;
		Idle();
	}
}