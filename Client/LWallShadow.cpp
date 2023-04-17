#include "LWallShadow.h"
#include "LImage.h"
#include "LMapManager.h"
namespace cl
{
	WallShadow::WallShadow(Scene* sc)
		:GameObject(sc, false)
	{
	}
	WallShadow::~WallShadow()
	{
	}
	void WallShadow::Initialize()
	{
		mShadow = AddComponent<SpriteRenderer>();
		GameObject::Initialize();
		mShadow->SetImage(Image::CreateEmptyImage(L"WallShadow", 24, 48, RGB(0, 0, 0)));
		mShadow->SetSprite(Sprite(Vector2(0, 0), Vector2(24, 48), Vector2(-12.0f, -27.0f)));
	}
	void WallShadow::Update()
	{
		float brightness = MapManager::GetLight(mIndex);
		mShadow->SetAlpha(brightness > 0.3f ? 255 * (1 - brightness) : 255);
		GameObject::Update();
	}
	void WallShadow::SetIndex(Vector2 index)
	{
		mIndex = index;
	}
}
