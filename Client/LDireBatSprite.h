#pragma once
#include "LCharacterSprite.h"
namespace cl
{
	class DireBatSprite : public CharacterSprite
	{
	public:
		DireBatSprite(Scene* sc);
		virtual ~DireBatSprite();

		virtual void Initialize() override;

		virtual void Turn(Vector2 dir) override;

		virtual void Jump()	 override {}
		virtual void Sink()	 override {}
		virtual void UnSink()override {}

		void SetY(int y);

	private:
		Vector2 mLookDir;
		std::wstring mLeftAnimation;
		std::wstring mRightAnimation;
		std::wstring mLeftShadowAnimation;
		std::wstring mRightShadowAnimation;
	};
}

