#pragma once
#include "LPiecesSprite.h"
namespace cl
{
	class KingSprite : public PiecesSprite
	{
	public:
		KingSprite(Scene* sc);
		~KingSprite() {};

		virtual void Initialize() override;
		virtual void Jump() override {};
	private:
	};
}
