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
		virtual bool OnAttacked(float attackPower, Vector2 dir) override;
		virtual Vector2 GetNextDir() override;
	private:
		AudioClip* mAttackSound;
		AudioClip* mDeathSound;
		AudioClip* mHitSound[3];
		AudioClip* mHeadLossSound[3];
		SkeletonSprite* mSkelSprite;
		float voiceVol = 60.0f;
		bool mbNoHead;
		bool mbPause;
		Vector2 mHitDir;
	};
}