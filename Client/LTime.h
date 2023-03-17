#pragma once
#include "CommonInclude.h"

namespace cl
{
	class Time
	{
	public:
		static void Initiailize();
		static void Update();
		static void Render(HDC hdc);

		__forceinline static double DeltaTime() { return mDeltaTime; }
		__forceinline static float FPS() { return fps; }

	private:
		static double mDeltaTime;
		static double mSecond;
		static float fps;
		static LARGE_INTEGER mCpuFrequency;
		static LARGE_INTEGER mPrevFrequency;
		static LARGE_INTEGER mCurFrequency;
	};
}
