#pragma once
#include "LBeatManager.h"
namespace cl
{
	class BeatObject
	{
	public:
		virtual ~BeatObject()
		{
			BeatManager::RemoveCharacters(this);
		}
		virtual void OnBeat() = 0;
		virtual void OnLateBeat() = 0;
		virtual void OnBeatChanged() = 0;
	};
}

