#pragma once
#include "LPieces.h"
namespace cl
{
	class Rook : public Pieces
	{
	public:
		Rook(Scene* sc);
		virtual ~Rook();;

		virtual void Initialize() override;
	private:
		virtual Vector2 GetNextDir()		override;
	};
}

