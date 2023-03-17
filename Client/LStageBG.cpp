#include "LStageBG.h"
#include "LSpriteRenderer.h"
namespace cl
{
	StageBG::StageBG()
		:GameObject(false)
	{
	}
	StageBG::~StageBG()
	{
	}
	void StageBG::Initialize()
	{
		GetSprite();
		GameObject::Initialize();
	}
	void StageBG::Update()
	{
		GameObject::Update();
	}
	void StageBG::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void StageBG::Release()
	{
		GameObject::Release();
	}
	void StageBG::GetSprite()
	{
		mRenderer = AddComponent<SpriteRenderer>();
		mRenderer->SetImage(L"stageBg", L"..\\FNFAssets\\Art\\24Bit\\Backgrounds\\Week1\\stage.bmp");
	}
}