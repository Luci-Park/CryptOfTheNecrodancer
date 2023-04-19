#pragma once
#include "LuciEngine.h"
namespace cl
{
	class TileLight
	{
	public:
		static bool _VisionThroughWalls;
	public:
		TileLight(Vector2 index);
		~TileLight();
		void AddIllumination(float brightness);
		float Illumination() { return mbIllumination; }
		bool IsRevealed() { return mbIsRevealed; }
		bool IsInSight() { return mbIsInSightLine && mbIllumination > 0.3f; }
		bool IsInSightLine() { return mbIsInSightLine; }
		void InSight() { mbIsInSightLine = true; }
		void Reset();
		void CheckIfInSight(Vector2 playerPos);
	private:
		float mbIllumination;
		bool mbIsInSightLine;
		bool mbIsRevealed;
		bool mbIsCompleteDark;
		Vector2 mIndex;
	};
}
