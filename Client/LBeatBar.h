#pragma once
#include "LGameObject.h"
#include "LSprite.h"
namespace cl
{
	class SpriteRenderer;
	class BeatBar : public GameObject
	{
	public:
		BeatBar(Scene* sc);
		~BeatBar();
		void SetBar(Vector2 spawnPos, Vector2 despawnPos, Vector2 direction, int beat, int prevBeat);
		void SetToUrgent();

		virtual void Update() override;
	private:
		bool CheckIfDespawn();
		void Move();

		SpriteRenderer* mSpriteRenderer;
		Sprite mNormalBeat;
		Sprite mUrgentBeat;
				
		Vector2 mSpawnPos;
		Vector2 mDespawnPos;
		Vector2 mDirection;
		int mMyBeat;
		int mBeatsInAdvance;
	};
}

