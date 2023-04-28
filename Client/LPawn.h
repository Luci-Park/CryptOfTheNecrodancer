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
		virtual void OnBeat() override;
	private:
		virtual Vector2 GetNextDir()		override;
	};
}

