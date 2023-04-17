#include "LTileObject.h"
namespace cl
{
	TileObject::TileObject(Scene* sc)
		:GameObject(sc, false)
	{
	}
	void TileObject::Initialize()
	{
		SetBrightness();
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
	void TileObject::CalLightBrightness()
	{
		Vector2 leftTop = Vector2(std::ceil(mIndex.x - outerRadius),std::ceil(mIndex.y - outerRadius));
		Vector2 rightBottom = Vector2(std::ceil(mIndex.x + outerRadius), std::ceil(mIndex.y + outerRadius));
		for (int i = leftTop.y; i <= rightBottom.y; ++i)
		{
			for (int j = leftTop.x; j <= rightBottom.x; ++j)
			{

			}
		}
		
	}

	float TileObject::CalLightBrightness(Vector2 tilePos, Vector2 lightPos, float innerRadius, float outerRadius)
	{
		float distance = Vector2::Distance(tilePos, lightPos);
		if (distance < innerRadius) return 1.0f;
		if (distance > outerRadius) return 0.0f;
		return 1.0 - (distance - innerRadius) / (outerRadius - innerRadius);
	}

}