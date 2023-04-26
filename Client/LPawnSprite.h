#pragma once
#include "LPiecesSprite.h"
namespace cl
{
	class PawnSprite : public PiecesSprite
	{
	public:
		PawnSprite(Scene* sc);
		~PawnSprite() {};

		virtual void Initialize() override;

	};
}