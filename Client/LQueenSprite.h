#pragma once
#include "LCharacterSprite.h"
namespace cl
{
	class QueenSprite : public CharacterSprite
	{
	public:
		QueenSprite(Scene* sc);
		~QueenSprite() {};

		virtual void Initialize() override;

		virtual void Turn(Vector2 dir) override {};
		virtual void Jump() override {};
	private:
	};
}
