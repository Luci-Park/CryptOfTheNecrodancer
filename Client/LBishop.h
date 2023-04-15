#pragma once
#include "LMonster.h"
namespace cl
{
	class BishopSprite;
	class Bishop :public Monster
	{
	public:
		Bishop(Scene* sc);
		virtual ~Bishop();

		virtual void Initialize()			override;
		void SetInitialBeat(int beat) { mBeatCount = beat%mMoveBeat; }
	private:
		virtual Vector2 GetNextDir()		override;
		virtual void SetStats()				override;

		virtual void PlayOnAttackSound();
		virtual void PlayOnHitSound();
		virtual void PlayOnDeathSound();

		virtual void Recoil(Vector2 dir)	override {};
		virtual void OnBeat()				override;
	private:
		BishopSprite* mBishopSprite;
		int mBeatCount;
		int mMoveBeat;

		AudioClip* mAttackSound;
		AudioClip* mDeathSounds[3];
	};
}

