#pragma once
#include "LCharacterSprite.h"
namespace cl
{
	class RedBatSprite : public CharacterSprite
	{
	public:
		RedBatSprite(Scene* sc);
		~RedBatSprite() {};

		virtual void Initialize() override;

		virtual void Turn(Vector2 dir) override;
		virtual void PlayAnimation() override;

		virtual void Jump()	 override {}
		virtual void Sink()	 override {}
		virtual void UnSink()override {}
	private:
		Vector2 mLookDir;
		std::wstring mLeftAnimation;
		std::wstring mRightAnimation;
		std::wstring mLeftShadowAnimation;
		std::wstring mRightShadowAnimation;
	};
}

