#include "LKnightSprite.h"
#include "LAnimator.h"
namespace cl
{

	KnightSprite::KnightSprite(Scene* sc)
		: CharacterSprite(sc)
	{
	}

	void KnightSprite::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		CharacterSprite::Initialize();
		mIdle = L"Idle";
		mReady = L"Ready";
		std::wstring path = L"..\\Assets\\Arts\\Boss\\Deep Blues\\Knight.bmp";
		mAnimator->CreateAnimation(mIdle, L"Knight", path, 4, 2, 0, 0, 4, -Vector2(92 * 0.25 * 0.5, 56 * 0.5f), 0.36f);
		path = L"..\\Assets\\Arts\\Boss\\Deep Blues\\Knight_Ready.bmp";
		mAnimator->CreateAnimation(mReady, L"Knight_Ready", path, 1, 2, 0, 0, 1, -Vector2(9, 56 * 0.5), 0.36f);
		Idle();
	}

	void KnightSprite::Ready()
	{
		if (!mAnimator->IsAnimationPlaying(mReady))
			mAnimator->Play(mReady, true, false);
	}

	void KnightSprite::Idle()
	{
		if (!mAnimator->IsAnimationPlaying(mIdle))
			mAnimator->Play(mIdle, true, false);
	}
}