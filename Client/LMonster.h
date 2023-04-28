#pragma once
#include "LGameCharacter.h"
#include "LObject.h"
#include "LAudioClip.h"
#include "LResources.h"
namespace cl
{
	class MonsterWeapon;
	class MonsterHeart;
	class Monster : public GameCharacter
	{
	public:
		enum class MoveState{NotMoved, Attacked, Dug, IsAsking, Moved, Failed, Unsunked};
		Monster(Scene* sc, bool isTouchingGround);
		virtual ~Monster();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual bool OnAttacked(float attackPower, Vector2 dir) override;
		virtual void OnAggroed(){};
		virtual void OnDestroy();

		virtual void OnBeat() override;
		virtual void OnLateBeat() override;
		virtual void OnBeatChanged();

	protected:
		//Do not advance next level at GetNextDir
		virtual Vector2 GetNextDir() = 0;
		virtual void SetStats() = 0;
		virtual void SetWeapon();
		virtual bool TryAttack(Vector2 Direction);
		//Returns true if InteractedWithDig;
		virtual bool TryDig(Vector2 direction);
		virtual bool TryMove() override;

		virtual void PlayOnAttackSound() = 0;
		virtual void PlayOnHitSound();
		virtual void PlayOnDeathSound();

		virtual Vector2 CardinalMoveTowards();
		virtual Vector2 DiagonalMoveTowards();
		virtual Vector2 CardinalMoveAway();
		virtual Vector2 DiagonalMoveAway();

		void Trample();

	private:
		void CheckAggro();
		void CheckActivation();
		void CheckShadow();
		bool IsNearPlayer();
	protected:
		bool mbIsActivated;
		bool mbIsAggroed;
		
		float mActivationRadius;
		float mAttackPower;
		int mDigPower;
		int mDrop;

		AudioClip* mGeneralHit;
		AudioClip* mGeneralDeath;
		MonsterWeapon* mWeapon;
		MonsterHeart* mHeart;

		MoveState mMoveState;
		Vector2 mNextDir;
		Vector2 mPrevDir;
	};
}

