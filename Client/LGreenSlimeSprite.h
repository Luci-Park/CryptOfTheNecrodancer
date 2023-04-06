#pragma once

#pragma once
#include "LCharacterSprite.h"
namespace cl
{
	class Animator;
	class GreenSlimeSprite : public CharacterSprite
	{
	public:
		GreenSlimeSprite(Scene* sc);
		~GreenSlimeSprite();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void Turn(Vector2 dir) override;
		virtual void OnBeatChanged() override;

		void Idle();
	private:
		Animator* mAnimator;
		Vector2 mLookDir;
	};
}

