#include "LTileObject.h"
#include "LMapManager.h"
#include "LTileLight.h"
namespace cl
{
	TileObject::TileObject(Scene* sc)
		:GameObject(sc, false)
		, mOuterRadius(0.0)
		, mInnerRadius(0.0)
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
		if (mInnerRadius == 0.0 && mOuterRadius == 0.0) return;
		Vector2 leftTop = Vector2(std::ceil(mIndex.x - mOuterRadius),std::ceil(mIndex.y - mOuterRadius));
		Vector2 rightBottom = Vector2(std::ceil(mIndex.x + mOuterRadius), std::ceil(mIndex.y + mOuterRadius));
		for (int i = leftTop.y; i <= rightBottom.y; ++i)
		{
			for (int j = leftTop.x; j <= rightBottom.x; ++j)
			{
				Vector2 pos = Vector2(j, i);
				MapManager::SetLight(pos, CalLightBrightness(pos, mIndex, mInnerRadius, mOuterRadius));
			}
		}
		
	}

	void TileObject::SetBrightness()
	{
		mInnerRadius = 0.0;
		mOuterRadius = 0.0;
	}

	float TileObject::CalLightBrightness(Vector2 tilePos, Vector2 lightPos, float innerRadius, float outerRadius)
	{
		float distance = Vector2::Distance(tilePos, lightPos);
		if (distance < innerRadius) return 1.0f;
		if (distance > outerRadius) return 0.0f;
		return 1.0 - (distance - innerRadius) / (outerRadius - innerRadius);
	}

}