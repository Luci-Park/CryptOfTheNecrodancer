#pragma once
#include"LMath.h"
namespace cl
{
	class Transform;
	class LightSource
	{
	public:
		LightSource(Transform* tr);
		LightSource(Transform* tr, float innerRadius, float outerRadius);
		~LightSource();
		void CalLightBrightness();
		void SetBrightness(float innerRadius, float outerRadius);
		bool IsActive();
	private:
		float CalLightBrightness(Vector2 tilePos, Vector2 lightPos, float innerRadius, float outerRadius);
		Transform* mTr;
		float mInnerRadius;
		float mOuterRadius;
	};
}

