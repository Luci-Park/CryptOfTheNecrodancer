#pragma once
#include "LGameObject.h"
namespace cl
{
	class Animator;
	class WeaponEffect : public GameObject
	{
	public:
		WeaponEffect(Scene* sc);
		virtual ~WeaponEffect();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void PlayEffect(Vector2 direction);
		void OnBeatChanged();
	protected:
		virtual void PlayUp() = 0;
		virtual void PlayDown() = 0;
		virtual void PlayRight() = 0;
		virtual void PlayLeft() = 0;
	protected:
		Animator* mAnimator;
	};
}

