#pragma once
#include "LCharacterSprite.h"
namespace cl
{
	class GreenDragonSprite : public CharacterSprite
	{
	public:
		GreenDragonSprite(Scene* sc);
		virtual ~GreenDragonSprite();

		virtual void Initialize() override;

		virtual void Turn(Vector2 dir) override;
	private:
			Vector2 mLookDir;
			std::wstring mLeftAnimation;
			std::wstring mRightAnimation;
			std::wstring mLeftShadowAnimation;
			std::wstring mRightShadowAnimation;
	};
}

