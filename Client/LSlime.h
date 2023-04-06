#pragma once
#include "LMonster.h"
namespace cl
{
	class AudioClip;
	class Slime : public Monster
	{
	public:
		Slime(Scene* sc);
		~Slime();

		virtual void PlayOnAttackSound() override;
		virtual void PlayOnHitSound() override;
		virtual void PlayOnDeathSound() override;
	private:
		AudioClip* mSlimeAttackSound;
		AudioClip* mSlimeDeathSound[3];
		AudioClip* mSlimeHitSound[3];
	};
}

