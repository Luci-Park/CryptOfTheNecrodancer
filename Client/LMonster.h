#pragma once
#include "LGameCharacter.h"
namespace cl
{
	class Monster : public GameCharacter
	{
	public:
		Monster(Scene* sc, bool isTouchingGround);
		virtual ~Monster();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void Sink() override;

		virtual void OnAttacked(float attackPower) = 0;
		virtual void OnDestroy() = 0;

		virtual void OnBeat() = 0;
		virtual void OnBeatChanged();

	protected:
		virtual bool TryAttack(Vector2 Direction) = 0;
		//Returns true if InteractedWithDig;
		virtual bool TryDig(Vector2 direction) = 0;
		virtual bool TryMove(Vector2 direction) = 0;

	protected:
		float mMaxHealth;
		float mHealth;
		float mAttack;
		int mDigPower;
		int mDrop;
	};
}

