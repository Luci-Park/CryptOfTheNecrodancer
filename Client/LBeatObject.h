#pragma once
#include "LConductor.h"
namespace cl
{
	class BeatObject
	{
	public:
		BeatObject()
		{
			Conductor::Instance().AddCharacters(this);
		}
		virtual ~BeatObject()
		{
			Conductor::Instance().RemoveCharacters(this);
		}
		virtual void OnBeat() = 0;
		virtual void OnLateBeat() = 0;
		virtual void OnBeatChanged() = 0;
	};
}

