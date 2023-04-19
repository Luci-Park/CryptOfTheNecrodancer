#pragma once
#include "LuciEngine.h"
namespace cl
{
	class TileLight
	{
	public:
		TileLight(Vector2 index);
		~TileLight();
		void AddIllumination(float brightness);
		float Illumination() { return mIllumination; }
		bool IsRevealed() { return mIsRevealed; }
		bool IsInSight() { return mIsInSightLine && mIllumination > 0.3f; }
		bool IsInSightLine() { return mIsInSightLine; }
		void InSight() { mIsInSightLine = true; }
		void Reset();
		void CheckIfInSight(Vector2 playerPos);
	private:
		float mIllumination;
		bool mIsInSightLine;
		bool mIsRevealed;
		Vector2 mIndex;
	};
}
