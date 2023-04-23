#include "LKingSprite.h"
#include "LAnimator.h"
namespace cl
{
	KingSprite::KingSprite(Scene* sc)
		:CharacterSprite(sc)
	{
	}
	void KingSprite::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		CharacterSprite::Initialize();
		std::wstring path = L"..\\Assets\\Arts\\Boss\\Deep Blues\\King.bmp";
		mAnimator->CreateAnimation(L"Idle", L"King", path, 4, 2, 0, 0, 4, -Vector2(13 * 0.5, 45), BeatManager::BeatDuration());
		mAnimator->Play(L"Idle", Animator::PlaySetting::Loop, false);
	}
}