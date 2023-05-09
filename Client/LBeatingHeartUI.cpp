#include "LBeatingHeartUI.h"
#include "LSpriteRenderer.h"
#include "LApplication.h"
#include "LTime.h"

extern::cl::Application application;
namespace cl
{
	BeatingHeartUI::BeatingHeartUI(Scene* sc)
		: GameObject(sc, true)
		, mbIsBeating(false)
		, mTimer(0.0)
	{
		mSpriteRenderer = GameObject::AddComponent<SpriteRenderer>();
		mSpriteRenderer->SetImage(L"HUD", L"..\\Assets\\Arts\\Effects\\HUD.bmp");
		mSmallHeart = Sprite(Vector2(117, 4), Vector2(34, 44), -Vector2(17, 22));
		mBigHeart = Sprite(Vector2(155, 0), Vector2(40, 50), -Vector2(20, 25));
		mSpriteRenderer->SetSprite(mSmallHeart);
	}
	BeatingHeartUI::~BeatingHeartUI()
	{
	}
	void BeatingHeartUI::Initialize()
	{
		GameObject::Initialize();
	}
	void BeatingHeartUI::Update()
	{
		GameObject::Update();
		if (mbIsBeating)
		{
			mSpriteRenderer->SetSprite(mBigHeart);
			mTimer += Time::DeltaTime();
			if (mTimer >= mBeatTime)
			{
				mbIsBeating = false;
				mSpriteRenderer->SetSprite(mSmallHeart);
			}
		}
	}
	void BeatingHeartUI::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void BeatingHeartUI::OnBeat()
	{
		if (mbIsBeating) return;
		mbIsBeating = true;
		mBeatTime = Conductor::Instance().SecondsPerBeat() * 0.25;
		mTimer = 0.0f;
	}
}