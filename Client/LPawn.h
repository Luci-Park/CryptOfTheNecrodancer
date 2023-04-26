#pragma once
#include "LPieces.h"
namespace cl
{
	class Pawn : public Pieces
	{
	public:
		Pawn(Scene* sc);
		virtual ~Pawn();;

		virtual void Initialize() override;
	private:
		virtual Vector2 GetNextDir()		override;
	};
}

