#include "LTime.h"
namespace cl
{
	double Time::mDeltaTime = 0.0l;
	double Time::mSecond = 0.0f;
	float Time::fps = 0.0f;
	LARGE_INTEGER Time::mCpuFrequency = {};
	LARGE_INTEGER Time::mPrevFrequency = {};
	LARGE_INTEGER Time::mCurFrequency = {};

	void Time::Initiailize()
	{
		QueryPerformanceFrequency(&mCpuFrequency);

		QueryPerformanceCounter(&mPrevFrequency);
	}

	void Time::Update()
	{
		QueryPerformanceCounter(&mCurFrequency);

		double differnceFrequency = mCurFrequency.QuadPart - mPrevFrequency.QuadPart;

		mDeltaTime = differnceFrequency / mCpuFrequency.QuadPart;
		
		mPrevFrequency.QuadPart = mCurFrequency.QuadPart;
	}

	void Time::Render(HDC hdc)
	{
		mSecond += mDeltaTime;

		if (mSecond > 1.0f)
		{
			fps = 1.0f / (float)mDeltaTime;
			mSecond = 0.0f;
		}
	}
}
