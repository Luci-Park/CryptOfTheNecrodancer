#include "LWallShadow.h"
#include "LImage.h"
#include "LMapManager.h"
#include "LTileLight.h"
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
		mShadow->SetImage(Image::CreateEmptyImage(L"WallShadow", 24, 40, RGB(0, 0, 0)));
		mShadow->SetSprite(Sprite(Vector2(0, 0), Vector2(24, 40), Vector2(-12.0f, -27.0f)));
	}
	void WallShadow::Update()
	{
		TileLight* light = MapManager::GetLight(mIndex);
		if (light->IsInSight())
		{
			mShadow->SetAlpha(255 * (1 - light->Illumination()));
		}
		else if (light->IsRevealed())
		{
			mShadow->SetAlpha(255 * 0.7);
		}
		else
		{
			mShadow->SetAlpha(255);
		}
		GameObject::Update();
	}
	void WallShadow::SetIndex(Vector2 index)
	{
		mIndex = index;
	}
}
