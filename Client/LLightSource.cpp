#include "LLightSource.h"
#include "LMapManager.h"
#include "LTransform.h"
#include "LGameObject.h"
namespace cl
{
	LightSource::LightSource(Transform* tr)
		: mInnerRadius(0.0)
		, mOuterRadius(0.0)
	{
		MapManager::AddLightSource(this);
		mTr = tr;
	}
	LightSource::LightSource(Transform* tr, float innerRadius, float outerRadius)
	{
		MapManager::AddLightSource(this);
		SetBrightness(innerRadius, outerRadius);
		mTr = tr;
	}
	LightSource::~LightSource()
	{
		MapManager::RemoveLightSource(this);
	}
	void LightSource::CalLightBrightness()
	{
		if (mInnerRadius == 0.0 && mOuterRadius == 0.0) return;
		Vector2 currIndex = mTr->GetPos() / UNITLENGTH;
		Vector2 leftTop = Vector2(std::ceil(currIndex.x - mOuterRadius), std::ceil(currIndex.y - mOuterRadius));
		Vector2 rightBottom = Vector2(std::ceil(currIndex.x + mOuterRadius), std::ceil(currIndex.y + mOuterRadius));
		for (int i = leftTop.y; i <= rightBottom.y; ++i)
		{
			for (int j = leftTop.x; j <= rightBottom.x; ++j)
			{
				Vector2 pos = Vector2(j, i);
				MapManager::SetLight(pos, CalLightBrightness(pos, currIndex, mInnerRadius, mOuterRadius));
			}
		}
	}
	void LightSource::SetBrightness(float innerRadius, float outerRadius)
	{
		mInnerRadius = innerRadius;
		mOuterRadius = outerRadius;
	}
	bool LightSource::IsActive()
	{
		return mTr->GetOwner()->IsActive();
	}
	float LightSource::CalLightBrightness(Vector2 tilePos, Vector2 lightPos, float innerRadius, float outerRadius)
	{
		float distance = Vector2::Distance(tilePos, lightPos);
		if (distance < innerRadius) return 1.0f;
		if (distance > outerRadius) return 0.0f;
		return 1.0 - (distance - innerRadius) / (outerRadius - innerRadius);
	}
}