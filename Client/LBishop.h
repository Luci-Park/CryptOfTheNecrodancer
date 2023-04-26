#pragma once
#include "LPieces.h"
namespace cl
{
	class BishopSprite;
	class Bishop :public Pieces
	{
	public:
		Bishop(Scene* sc);
		virtual ~Bishop();

		virtual void Initialize()			override;
	private:
		virtual Vector2 GetNextDir()		override;
	};
}

