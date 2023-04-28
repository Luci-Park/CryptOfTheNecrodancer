#pragma once
#include "LMonster.h"
namespace cl
{
	class Queen: public Monster
	{
	public:
		Queen(Scene* sc);
		virtual ~Queen(){}

		virtual void Initialize() override;
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
	};
}

