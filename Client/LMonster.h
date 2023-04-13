#pragma once
#include "LGameCharacter.h"
namespace cl
{
	class MonsterWeapon;
	class AudioClip;
	class MonsterHeart;
	class Monster : public GameCharacter
	{
	public:
		Monster(Scene* sc, bool isTouchingGround);
		virtual ~Monster();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void Sink() override;

		virtual void OnAttacked(float attackPower) override;
		virtual void OnDestroy();

		virtual void OnBeat() override;
		virtual void OnBeatChanged();

	protected:
		virtual void SetStats() = 0;
		virtual void SetWeapon();
		virtual Vector2 GetNextDir() = 0;
		virtual bool TryAttack(Vector2 Direction);
		//Returns true if InteractedWithDig;
		virtual bool TryDig(Vector2 direction);
		virtual bool TryMove(Vector2 direction);

		virtual void PlayOnAttackSound() = 0;
		virtual void PlayOnHitSound();
		virtual void PlayOnDeathSound();
	protected:
		AudioClip* mGeneralHit;
		AudioClip* mGeneralDeath;
		float mAttackPower;
		int mDigPower;
		int mDrop;
		MonsterWeapon* mWeapon;
		MonsterHeart* mHeart;
	};
}

