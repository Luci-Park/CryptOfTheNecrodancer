#pragma once
#include "LMonster.h"
namespace cl
{
	class ZombieSprite;
	class Zombie : public Monster
	{
	public:
		Zombie(Scene* sc);
		virtual ~Zombie();

		virtual void Initialize() override;
		virtual bool TryAttack(Vector2 direction) override;
		virtual bool TryMove(Vector2 direction) override;

		virtual void OnBeat() override;
		virtual void OnLateBeat() override;

		virtual void PlayOnAttackSound() override;
		virtual void PlayOnHitSound() override;
		virtual void PlayOnDeathSound() override;
	protected:
		virtual void SetStats() override;
		virtual Vector2 GetNextDir() override;
	private:
		ZombieSprite* mZombieSprite;
		AudioClip* mAttackSound;
		AudioClip* mDeathSound;
		Vector2 mMoveDir;
		bool mbBeat;
		bool mbFlip;
	};
}

