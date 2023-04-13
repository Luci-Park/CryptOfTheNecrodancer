#pragma once
#include "LMonster.h"
namespace cl
{
	class AudioClip;
	class Bat : public Monster
	{
	public:
		Bat(Scene* sc);
		virtual ~Bat();


		virtual void Initialize() override;

		virtual void Sink() override{}
		virtual bool UnSink() override { return false; }
		virtual void MoveFailed(Vector2 dir) override {};

		virtual void PlayOnAttackSound() override;
		virtual void PlayOnHitSound() override;
		virtual void PlayOnDeathSound() override;
	private:
		virtual void SetStats() override;
		virtual Vector2 GetNextDir() override;
		virtual bool TryMove(Vector2 direction) override;

	private:
		AudioClip* mAttackSound;
		AudioClip* mDeathSound;
		AudioClip* mHitSound;
		float voiceVol = 60.0f;
		bool mbMove;
	};
}

