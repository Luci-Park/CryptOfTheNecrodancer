#pragma once
#include "LMonster.h"
namespace cl
{
	class BatBase : public Monster
	{
	public:
		BatBase(Scene* sc);
		virtual ~BatBase();
		virtual void Sink() override {}
		virtual bool UnSink() override { return false; }
		virtual void Recoil(Vector2 dir) override {};

		virtual void PlayOnAttackSound() override;
		virtual void PlayOnHitSound() override;
		virtual void PlayOnDeathSound() override;

	protected:
		virtual void SetStats() override = 0;
		virtual Vector2 GetNextDir() override;

	private:
		AudioClip* mAttackSound;
		AudioClip* mDeathSound;
		AudioClip* mHitSound;
	};
}

