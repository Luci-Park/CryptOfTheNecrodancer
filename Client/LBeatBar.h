#pragma once
#include "LGameObject.h"
#include "LSprite.h"
namespace cl
{
	class SpriteRenderer;
	class BeatJudge;
	class BeatBar : public GameObject
	{
	public:
		BeatBar(Scene* sc);
		~BeatBar();
		void SetBar(BeatJudge* ui, Vector2 spawnPos, Vector2 despawnPos, Vector2 direction, int beat, int prevBeat);
		void SetToUrgent();

		virtual void Update() override;
	private:
		bool CheckIfDespawn();
		bool IsOnBeat();
		void Move();

		SpriteRenderer* mSpriteRenderer;
		Sprite mNormalBeat;
		Sprite mUrgentBeat;
				
		BeatJudge* mMaster;
		Vector2 mSpawnPos;
		Vector2 mDespawnPos;
		Vector2 mDirection;
		float mMyBeat;
		int mBeatsInAdvance;
	};
}

