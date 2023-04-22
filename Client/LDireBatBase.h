#pragma once
#include "LMonster.h"
#include "LLightSource.h"
namespace cl
{
	class DireBatBase : public Monster
	{
	public:
		DireBatBase(Scene* sc);
		virtual ~DireBatBase();

		virtual void Initialize() override;

		virtual void Recoil(Vector2 dir) override {};
		virtual void OnAggroed() override;
		virtual void OnLateBeat() override;

		virtual void PlayOnAttackSound() override;
		virtual void PlayOnHitSound() override;
		virtual void PlayOnDeathSound() override;

	private:
		virtual void SetStats() = 0;
		virtual Vector2 GetNextDir() override;
		virtual int GetY() = 0;

	private:
		LightSource* mLightSource;

		AudioClip* mAttackSound;
		AudioClip* mDeathSound;
		AudioClip* mHitSounds[3];
		AudioClip* mCrySound;
		bool mbMove;
	};
}

