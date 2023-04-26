#pragma once
#include "LPiecesSprite.h"
namespace cl
{
	class BishopSprite : public PiecesSprite
	{
	public:
		enum class State {Idle, Ready};
		BishopSprite(Scene* sc);
		~BishopSprite() {};

		virtual void Initialize() override;
	};
}

