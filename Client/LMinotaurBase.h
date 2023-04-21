#pragma once
#include "LMonster.h"

namespace cl
{
	class MinotaurSprite;
	class MinotaurBase : public Monster
	{
	public:
		enum class State{Idle, Charge, Faint};
		MinotaurBase(Scene* sc);
		virtual ~MinotaurBase();

		virtual void Initialize() override;

		virtual void OnAggroed() override;
		virtual void OnLateBeat() override;
		virtual bool TryDig(Vector2 direction) override;


		virtual void PlayOnAttackSound() override;
		virtual void PlayOnHitSound() override;
		virtual void PlayOnDeathSound() override;

	protected:
		virtual void SetStats() = 0;
		virtual Vector2 GetNextDir() override;
		virtual int GetY() = 0;

		Vector2 IsInSight();
		void ChangeState(State state);
	private:
		MinotaurSprite* mMinoSprite;
		AudioClip* mAttackSound;
		AudioClip* mDeathSound;
		AudioClip* mHitSounds[4];
		AudioClip* mCrySound;
		AudioClip* mChargeSound;
		AudioClip* mWallImpactSound;
		int mBeatCount;
		State mMinoState;
	};
}

