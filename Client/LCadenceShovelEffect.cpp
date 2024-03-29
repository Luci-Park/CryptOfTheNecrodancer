#include "LCadenceShovelEffect.h"
#include "LSpriteRenderer.h"
#include "LConductor.h"
#include "LTime.h"
namespace cl
{
	CadenceShovelEffect::CadenceShovelEffect(Scene* sc)
		: GameObject(sc, false)
		, mSpriteRenderer(nullptr)
	{
	}
	CadenceShovelEffect::~CadenceShovelEffect()
	{
	}
	void CadenceShovelEffect::Initialize()
	{
		mSpriteRenderer = AddComponent<SpriteRenderer>();
		mSpriteRenderer->SetImage(L"Shovels", L"..\\Assets\\Arts\\Items\\Shovels.bmp");
		mSpriteRenderer->SetActive(false);
	}
	void CadenceShovelEffect::Update()
	{
		if (mbIsShowing) Show();
		GameObject::Update();
	}
	void CadenceShovelEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void CadenceShovelEffect::OnDig(WallTile* wallTile, Sprite sprite)
	{
		mSpriteRenderer->SetActive(true);
		mbIsShowing = true;
		mTransform->SetPos(wallTile->GetPlateCenter());
		mSpriteRenderer->SetSprite(sprite);
	}
	void CadenceShovelEffect::Show()
	{
		showTime = Conductor::Instance().SecondsPerBeat()*0.75;
		timer += Time::DeltaTime();
		if (showTime <= timer)
		{
			Reset();
		}
	}
	void CadenceShovelEffect::Reset()
	{
		timer = 0.0f;
		mSpriteRenderer->SetActive(false);
		mbIsShowing = false;
	}
}