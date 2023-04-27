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
		static AttackDir GetDir(Vector2 dir);
		Knight(Scene* sc);
		virtual ~Knight();
		virtual void Initialize() override;
		Vector2 GetPlayerAttackDir();
		Vector2 GetMoveDir();
	private:
		virtual Vector2 GetNextDir() override;

		static Vector2 _AttackDirections[(int)AttackDir::Size];
	};
}

