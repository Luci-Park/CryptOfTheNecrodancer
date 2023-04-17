#include "LFloorShadow.h"
#include "LImage.h"
#include "LMapManager.h"
namespace cl
{
	FloorShadow::FloorShadow(Scene* sc)
		:GameObject(sc, false)
	{

	}
	FloorShadow::~FloorShadow()
	{
	}
	void FloorShadow::Initialize()
	{
		mShadow = AddComponent<SpriteRenderer>();
		GameObject::Initialize();
		mShadow->SetImage(Image::CreateEmptyImage(L"FloorShadow", DEFAULTUNIT, DEFAULTUNIT, RGB(0, 0, 0)));
		mShadow->SetSprite(Sprite(Vector2(0, 0), Vector2(DEFAULTUNIT, DEFAULTUNIT), Vector2(DEFAULTUNIT, DEFAULTUNIT) * -0.5));
	}
	void FloorShadow::Update()
	{
		float brightness = MapManager::GetLight(mIndex);
		mShadow->SetAlpha(brightness > 0.3f ? 255 * (1-brightness) : 255);
		GameObject::Update();
	}
	void FloorShadow::SetIndex(Vector2 index)
	{
		mIndex = index;
	}
}
