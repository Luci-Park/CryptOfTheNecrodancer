#pragma once
#include "LPiecesSprite.h"
namespace cl
{
	class KnightSprite : public PiecesSprite
	{
	public:
		KnightSprite(Scene* sc);
		~KnightSprite() {};

		virtual void Initialize() override;

	};
}

