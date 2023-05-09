#pragma once
#include "LGameObject.h"
namespace cl
{
	class BeatBar;
	class BeatUI : public GameObject
	{
	public:
		BeatUI(Scene* sc);
		~BeatUI();
		
		virtual void Initialize() override;
		virtual void Update() override;

		void LeftBeatEnter(BeatBar* bar);
		void RightBeatEnter(BeatBar* bar);
		void LeftBeatExit(BeatBar* bar);
		void RightBeatExit(BeatBar* bar);

		void DespawnCurrentBeat();
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

