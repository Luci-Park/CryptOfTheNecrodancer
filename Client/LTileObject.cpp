#include "LTileObject.h"
namespace cl
{
	TileObject::TileObject(Scene* sc)
		:GameObject(sc, false)
	{
	}
	void TileObject::Initialize()
	{
		GameObject::Initialize();
	}
	void TileObject::Update()
	{
		GameObject::Update();
	}
	void TileObject::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}