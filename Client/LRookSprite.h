#pragma once
#include "LPiecesSprite.h"
namespace cl
{
	class RookSprite : public PiecesSprite
	{
	public:
		enum class State { Idle, Ready };
		RookSprite(Scene* sc);
		~RookSprite() {};

		virtual void Initialize() override;

	};
}

