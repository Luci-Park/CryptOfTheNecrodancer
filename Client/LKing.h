#pragma once
#include "LMonster.h"
namespace cl
{
	class KingSprite;
	class King : public Monster
	{
	public:
		King(Scene* sc);
		virtual ~King(){}

		virtual void Initialize() override;
		virtual void Update() override;
		void StartAttack();
	private:
		virtual Vector2 GetNextDir()		override;
		virtual void SetStats()				override;

		virtual void PlayOnAttackSound();
		virtual void PlayOnHitSound();
		virtual void PlayOnDeathSound();

		virtual void Recoil(Vector2 dir)	override {};

		Vector2 MoveAwayPlayer();
		Vector2 MoveTowardsPlayer();
	private:
		KingSprite* mKingSprite;
		bool mbStartAttack;
		AudioClip* mAttackSounds[7];
		AudioClip* mDeathSound;
		AudioClip* mHitSounds[4];
		AudioClip* mCry;
	};
}

