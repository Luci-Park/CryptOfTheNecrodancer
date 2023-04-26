#pragma once
#include "LPieces.h"
namespace cl
{
	class Knight : public Pieces
	{
	public:
		Knight(Scene* sc);
		virtual ~Knight();
		virtual void Initialize() override;
	private:
		virtual Vector2 GetNextDir()		override;
	};
}

