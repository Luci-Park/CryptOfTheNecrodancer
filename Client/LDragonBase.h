#pragma once
#include "LMonster.h"
namespace cl
{
	class DragonBase : public Monster
	{
	public:
		enum class State{Idle, ReadyFire, Fire};
		DragonBase(Scene* sc);
		virtual ~DragonBase();

		virtual void Initialize() override;

		virtual void OnAggroed() override;
		virtual void OnLateBeat() override;

		virtual void PlayOnAttackSound() override;
		virtual void PlayOnHitSound() override;
		virtual void PlayOnDeathSound() override;
	protected:
		virtual void SetStats() = 0;
		virtual Vector2 GetNextDir() override;

		void PlayWalkSound();
		void SetDragonState(State state);
	protected:
		AudioClip* mAttackSound;
		AudioClip* mDeathSound;
		AudioClip* mHitSounds[3];
		AudioClip* mCrySound;
		AudioClip* mWalkSounds[3];
		AudioClip* mPrefireSound;
		AudioClip* mFireSound;

		int mBeatCount;
		State mDragonState;
	};
}

