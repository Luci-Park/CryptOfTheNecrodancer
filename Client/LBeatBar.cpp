#include "LBeatBar.h"
#include "LSpriteRenderer.h"
#include "LTime.h"
namespace cl
{
	BeatBar::BeatBar(Scene* sc)
		:GameObject(sc, true)
	{
		mTransform->SetScale(Vector2::One * UNITSCALE);
		mSpriteRenderer = AddComponent<SpriteRenderer>();
		mSpriteRenderer->SetImage(L"HUD", L"..\\Assets\\Arts\\Effects\\HUD.bmp");
		mNormalBeat = Sprite(Vector2(200, 10), Vector2(6, 30), -Vector2(3, 15));
		mUrgentBeat = Sprite(Vector2(218, 10), Vector2(6, 30), -Vector2(3, 15));
		mSpriteRenderer->SetSprite(mNormalBeat);
	}
	BeatBar::~BeatBar()
	{
	}
	void BeatBar::SetToUrgent()
	{
		mSpriteRenderer->SetSprite(mUrgentBeat);
	}
}