#pragma once
#include "LMonster.h"
#include "LLightSource.h"
namespace cl
{
	class Queen: public Monster
	{
	public:
		Queen(Scene* sc);
		virtual ~Queen();

		virtual void Initialize() override;
		void SetInitialBeat(int beat) { mBeatCount = beat; }
		virtual void OnLateBeat() override;
	private:
		virtual Vector2 GetNextDir()		override;
		virtual void SetStats()				override;

		virtual void PlayOnAttackSound()	override;
		virtual void PlayOnHitSound()		override;
		virtual void PlayOnDeathSound()		override;

		void PlaySing();
	private:
		AudioClip* mDeathSounds[3];
		AudioClip* mSingSounds[6];
		int mBeatCount;
		LightSource* mLight;
	};
}

