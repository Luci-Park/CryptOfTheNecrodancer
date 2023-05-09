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

		void SetCurrentBar(BeatBar* bar);
		void UnsetCurrentBar(BeatBar* bar);
		void DespawnCurrentBar();
	private:
		int mBeatsShownInAdvance;
		int mNextBeatToShow;
		Vector2 mRightSpawn;
		Vector2 mLeftSpawn;
		Vector2 mDespawnPoint;

		BeatBar* mCurrentBeat;
	};
}

