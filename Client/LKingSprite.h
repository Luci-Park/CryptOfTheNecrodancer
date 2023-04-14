#pragma once
#include "LCharacterSprite.h"
namespace cl
{
	class KingSprite : public CharacterSprite
	{
	public:
		KingSprite(Scene* sc);
		~KingSprite() {};

		virtual void Initialize() override;

		virtual void Turn(Vector2 dir) override {};
		virtual void Jump() override {};
	private:
	};
}
