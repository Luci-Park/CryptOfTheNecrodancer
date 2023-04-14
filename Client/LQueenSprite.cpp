#include "LQueenSprite.h"
#include "LAnimator.h"
namespace cl
{
	QueenSprite::QueenSprite(Scene* sc)
		:CharacterSprite(sc)
	{
	}
	void QueenSprite::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		CharacterSprite::Initialize();
		std::wstring path = L"..\\Assets\\Arts\\Boss\\Deep Blues\\Queen.bmp";
		mAnimator->CreateAnimation(L"Idle", L"Queen", path, 1, 2, 0, 0, 1, -Vector2(33 * 0.5f, 78 * 0.5f), 0.36f);
		mAnimator->Play(L"Idle", true, false);
	}
}