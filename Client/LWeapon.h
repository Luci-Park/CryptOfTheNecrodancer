#pragma once
#include "LGameObject.h"
namespace cl
{
	class Animator;
	class Weapon : public GameObject
	{
	public:
		Weapon(Scene* sc);
		~Weapon();

		void Initialize() override;
		void Update() override;
		void Render(HDC hdc) override;

		void OnBeatChanged();
		void PlayAttackAnimation(Vector2 dir);
		bool Attack(Vector2 srcIdx, Vector2 input);

	protected:
		virtual void SetAnimation() = 0;
		virtual Vector2 EffectPos(Vector2 dir) = 0;
		virtual std::wstring SelectAnimation(Vector2 dir) = 0;
		virtual bool TryAttack(Vector2 srcIdx, Vector2 input) = 0;
	protected:
		float mPower;
		Animator* mAnimator;
	};
}

