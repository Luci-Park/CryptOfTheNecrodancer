#pragma once
#include "LMonster.h"
namespace cl
{
	class AudioClip;
	class SkeletonSprite;
	class SkeletonBase : public Monster
	{
	public:
		SkeletonBase(Scene* sc);
		virtual ~SkeletonBase();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void PlayOnAttackSound() override;
		virtual void PlayOnHitSound() override;
		virtual void PlayOnDeathSound() override;
		virtual void OnLateBeat() override;
	protected:
		virtual int GetY() = 0;
	private:
		void PlayOnHeadLossSound();
		virtual void SetStats() = 0;
		virtual void OnAttacked(float attackPower) override;
		virtual Vector2 GetNextDir() override;
		Vector2 MoveTowardsPlayer();
		Vector2 MoveAwayFromPlayer();
	private:
		AudioClip* mAttackSound;
		AudioClip* mDeathSound;
		AudioClip* mHitSound[3];
		AudioClip* mHeadLossSound[3];
		SkeletonSprite* mSkelSprite;
		float voiceVol = 60.0f;
		bool mbNoHead;
		bool mbPause;
		Vector2 mRunDir;
	};
}