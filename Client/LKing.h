#pragma once
#include "LMonster.h"
namespace cl
{
	class King : public Monster
	{
	public:
		King(Scene* sc);
		virtual ~King(){}

		virtual void Initialize() override;
		virtual void Update() override;

		virtual bool OnAttacked(float attackPower, Vector2 dir) override;
		virtual void OnLateBeat() override;

		void StartAttack();
	private:
		virtual Vector2 GetNextDir()		override;
		virtual void SetStats()				override;

		virtual void PlayOnAttackSound();
		virtual void PlayOnHitSound();
		virtual void PlayOnDeathSound();

		virtual void Recoil(Vector2 dir)	override {};

	private:
		bool mbStartAttack;
		AudioClip* mAttackSounds[7];
		AudioClip* mDeathSound;
		AudioClip* mHitSounds[4];
		AudioClip* mCry;
		Vector2 mAttackedDir;
		int mBeatCount;
	};
}

