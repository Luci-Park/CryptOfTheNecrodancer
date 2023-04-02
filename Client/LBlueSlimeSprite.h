#pragma once
#include "LCharacterSprite.h"
namespace cl
{
	class Animator;
	class BlueSlimeSprite : public CharacterSprite
	{
	public:
		BlueSlimeSprite(Scene* sc);
		~BlueSlimeSprite();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void Turn(Vector2 dir) override;
		virtual void OnBeatChanged() override;

		void Idle();
		virtual void Jump() override;
	private:
		Animator* mAnimator;
		Vector2 mLookDir;
	};
}

