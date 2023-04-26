#pragma once
#include "LPiecesSprite.h"
namespace cl
{
	class QueenSprite : public PiecesSprite
	{
	public:
		QueenSprite(Scene* sc);
		~QueenSprite() {};

		virtual void Initialize() override;
		virtual void Jump() override {};
	private:
	};
}
