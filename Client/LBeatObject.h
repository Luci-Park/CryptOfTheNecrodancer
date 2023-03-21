#pragma once
namespace cl
{
	class BeatObject
	{
	public:
		virtual void OnBeat() = 0;
		virtual void OnBeatChanged() = 0;
	};
}

