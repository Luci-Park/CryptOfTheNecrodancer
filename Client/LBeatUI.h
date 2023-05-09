#pragma once
#include "LGameObject.h"
namespace cl
{
	class BeatUI : public GameObject
	{
	public:
		BeatUI(Scene* sc);
		~BeatUI();
		
		virtual void Initialize() override;
		virtual void Update() override;

	private:
		int mBeatsShownInAdvance;
		int mNextBeatToShow;
		Vector2 mRightSpawn;
		Vector2 mLeftSpawn;
		Vector2 mDespawnPoint;
	};
}

