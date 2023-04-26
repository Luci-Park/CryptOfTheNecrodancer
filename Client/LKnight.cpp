#include "LKnight.h"
namespace cl
{
	Knight::Knight(Scene* sc)
		:Pieces(sc)
	{
		mMoveBeat = 4;
		mAttackDirections[(int)AttackDir::DownLeft] = Vector2(-2, 1);
		mAttackDirections[(int)AttackDir::DownRight] = Vector2(2, 1);
		mAttackDirections[(int)AttackDir::LeftDown] = Vector2(-1, 2);
		mAttackDirections[(int)AttackDir::LeftUp] = Vector2(-1, -2);
		mAttackDirections[(int)AttackDir::RightDown] = Vector2(1, 2);
		mAttackDirections[(int)AttackDir::RightUp] = Vector2(1, -2);
		mAttackDirections[(int)AttackDir::UpLeft] = Vector2(-2, -1);
		mAttackDirections[(int)AttackDir::UpRight] = Vector2(2, -1);
	}
	Knight::~Knight()
	{
	}
	void Knight::Initialize()
	{
	}
	Vector2 Knight::GetNextDir()
	{
		return Vector2();
	}
}