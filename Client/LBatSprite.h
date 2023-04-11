#pragma once
#include "LCharacterSprite.h"
namespace cl
{
	class BatSprite : public CharacterSprite
	{
	public:
		BatSprite(Scene* sc);
		~BatSprite() {};

		virtual void Initialize() override;

		virtual void Turn(Vector2 dir) override;

		virtual void Jump() override {};
	private:
		Vector2 mLookDir;
		std::wstring leftAnimation;
		std::wstring rightAnimation;		
	};
}

