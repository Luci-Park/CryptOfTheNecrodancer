#pragma once
#include "LGameObject.h"
namespace cl
{
	class Animator;
	class CadenceAttackEffect : public GameObject
	{
	public:
		CadenceAttackEffect(Scene* sc);
		~CadenceAttackEffect();
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void OnBeatChanged();
		void OnAttack(Vector2 dir);
	private:
		Animator* mAnimator;
	};
}

