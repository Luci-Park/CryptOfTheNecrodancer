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
		mFull = Sprite(Vector2(0, 0), Vector2(24, 22), Vector2(-12, -11));
		mHalf = Sprite(Vector2(29, 0), Vector2(24, 22), Vector2(-12, -11));
		mEmpty = Sprite(Vector2(58, 0), Vector2(24, 22), Vector2(-12, -11));
	}
	HeartContainerUI::~HeartContainerUI()
	{
	}
	CursedHeartUI::CursedHeartUI(Scene* sc)
		:HeartUI(sc)
	{
		//SetSprite
		mFull = Sprite(Vector2(0, 27), Vector2(24, 22), Vector2(-12, -11));
		mHalf = Sprite(Vector2(29, 27), Vector2(24, 22), Vector2(-12, -11));
		mEmpty = Sprite(Vector2(58, 27), Vector2(24, 22), Vector2(-12, -11));
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
