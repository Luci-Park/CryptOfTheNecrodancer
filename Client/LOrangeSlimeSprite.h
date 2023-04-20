#pragma once
#include "LCharacterSprite.h"
namespace cl
{
	class OrangeSlimeSprite : public CharacterSprite
	{
	public:
		OrangeSlimeSprite(Scene* sc);
		~OrangeSlimeSprite();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void Turn(Vector2 dir) override;
		virtual void OnBeatChanged() override;

		void JumpAnimation();
	private:
		Vector2 mLookDir;
	};
}

