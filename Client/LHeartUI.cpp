#include "LHeartUI.h"
#include "LSpriteRenderer.h"
namespace cl
{
	HeartUI::HeartUI(Scene* sc)
		:GameObject(sc, true)
	{
		mTransform->SetScale(Vector2::One * UNITSCALE);
		mSpriteRenderer = AddComponent<SpriteRenderer>();
		mSpriteRenderer->SetImage(L"HUD", L"..\\Assets\\Arts\\Effects\\HUD.bmp");
		SetHeart(State::Full);
	}
	HeartUI::~HeartUI()
	{
	}
	void HeartUI::SetHeart(State state)
	{
		if (State::Full == state)
			mSpriteRenderer->SetSprite(mFull);
		if (State::Half == state)
			mSpriteRenderer->SetSprite(mHalf);
		if (State::Empty == state)
			mSpriteRenderer->SetSprite(mEmpty);
	}
	HeartContainerUI::HeartContainerUI(Scene* sc)
		:HeartUI(sc)
	{
		//SetSprite
	}
	HeartContainerUI::~HeartContainerUI()
	{
	}
	CursedHeartUI::CursedHeartUI(Scene* sc)
		:HeartUI(sc)
	{
		//SetSprite
	}
	CursedHeartUI::~CursedHeartUI()
	{
	}
	void CursedHeartUI::SetHeart(State state)
	{
		HeartUI::SetHeart(state);
		if (State::Empty == state)
			Destroy();
	}
}
