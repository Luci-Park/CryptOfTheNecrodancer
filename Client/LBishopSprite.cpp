#include "LBishopSprite.h"
#include "LAnimator.h"
namespace cl
{
	BishopSprite::BishopSprite(Scene* sc)
		: PiecesSprite(sc)
	{
	}

	void BishopSprite::Initialize()
	{
		PiecesSprite::Initialize();
		std::wstring path = L"..\\Assets\\Arts\\Boss\\Deep Blues\\Bishop.bmp";
		mAnimator->CreateAnimation(mIdle, L"Bishop", path, 4, 2, 0, 0, 4, -Vector2(13 * 0.5, 32), BeatManager::BeatDuration() * 2);
		mAnimator->CreateAnimation(mShadowIdle, L"Bishop", path, 4, 2, 0, 1, 4, -Vector2(13 * 0.5, 32), BeatManager::BeatDuration() * 2);
		path = L"..\\Assets\\Arts\\Boss\\Deep Blues\\Bishop_Ready.bmp";
		mAnimator->CreateAnimation(mReady, L"Bishop_Ready", path, 1, 2, 0, 0, 1, -Vector2(17 *0.5, 32), BeatManager::BeatDuration());
		mAnimator->CreateAnimation(mShadowReady, L"Bishop_Ready", path, 1, 2, 0, 1, 1, -Vector2(17 *0.5, 32), BeatManager::BeatDuration());
		Idle();
	}


	void BishopSprite::OnBeatChanged()
	{
		mAnimator->SetDuration(BeatManager::BeatDuration() * 2);
	}
}
