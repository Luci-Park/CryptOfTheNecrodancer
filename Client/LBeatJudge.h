#pragma once
#include "LGameObject.h"
namespace cl
{
	class BeatBar;
	class BeatJudge : public GameObject
	{
	public:
		BeatJudge(Scene* sc);
		~BeatJudge();
		
		virtual void Initialize() override;
		virtual void Update() override;

		void LeftBeatEnter(BeatBar* bar);
		void RightBeatEnter(BeatBar* bar);
		void LeftBeatExit(BeatBar* bar);
		void RightBeatExit(BeatBar* bar);

		void OnValidInput();
		bool IsInBeat();
	private:
		int mBeatsShownInAdvance;
		int mNextBeatToShow;
		Vector2 mRightSpawn;
		Vector2 mLeftSpawn;
		Vector2 mDespawnPoint;

		BeatBar* mCurrentLeftBeat;
		BeatBar* mCurrentRightBeat;
	};
}

