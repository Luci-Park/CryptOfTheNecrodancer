#pragma once
#include "LItem.h"
namespace cl
{
	class Animator;
	class Cadence;
	class Weapon : public Item
	{
	public:
		Weapon(Scene* sc);
		~Weapon();

		void Initialize() override;
		void Update() override;
		void Render(HDC hdc) override;
		virtual bool Use(Cadence* player) override;

		void OnBeatChanged();
		void PlayAttackAnimation(Vector2 dir);
		bool Attack(Vector2 srcIdx, Vector2 input);
		bool isMelee() { return mbIsMelee; }
	protected:
		virtual void SetSprite() = 0;
		virtual void SetAnimation() = 0;
		virtual Vector2 EffectPos(Vector2 dir) = 0;
		virtual std::wstring SelectAnimation(Vector2 dir) = 0;
		virtual bool TryAttack(Vector2 srcIdx, Vector2 input) = 0;
	protected:
		float mPower;
		Animator* mAnimator;
		bool mbIsMelee;
	};
}

