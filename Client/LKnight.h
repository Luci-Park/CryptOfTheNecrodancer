#pragma once
#include "LPieces.h"
namespace cl
{
	class Knight : public Pieces
	{
	public:
		enum class AttackDir {
			DownLeft, DownRight, LeftDown, LeftUp,
			RightDown, RightUp, UpLeft, UpRight,
			Size
		};
		Knight(Scene* sc);
		virtual ~Knight();
		virtual void Initialize() override;
	private:
		virtual Vector2 GetNextDir() override;
		Vector2 mAttackDirections[(int)AttackDir::Size];
	};
}

