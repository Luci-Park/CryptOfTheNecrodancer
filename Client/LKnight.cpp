#include "LKnight.h"
#include "LKnightSprite.h"
#include "LMapManager.h"
#include "LKnightWeapon.h"
namespace cl
{
	Vector2 Knight::_AttackDirections[(int)AttackDir::Size] =
	{
		Vector2(-2, 1),Vector2(2, 1), 
		Vector2(-1, 2),Vector2(-1, -2), 
		Vector2(1, 2), Vector2(1, -2),
		Vector2(-2, -1), Vector2(2, -1)
	};
	Knight::AttackDir Knight::GetDir(Vector2 dir)
	{
		for (int i = 0; i < (int)AttackDir::Size; ++i)
		{
			if (dir == _AttackDirections[i])
				return (AttackDir)i;
		}
		return AttackDir::Size;
	}
	Knight::Knight(Scene* sc)
		:Pieces(sc)
	{
		mMoveBeat = 4;
	}
	Knight::~Knight()
	{
	}
	void Knight::Initialize()
	{
		Monster::Initialize();
		mPieceSprite = object::Instantiate<KnightSprite>(GameObject::GetScene(), mTransform, mTransform->GetPos(), eLayerType::Monster);
		mSprite = mPieceSprite;
	}
	Vector2 Knight::GetPlayerAttackDir()
	{
		for (int i = 0; i < ((int)AttackDir::Size); i++)
		{
			if (MapManager::GetPlayerOnIndex(mIndex + _AttackDirections[i]) != nullptr)
				return _AttackDirections[i];
		}
		return Vector2::Zero;
	}
	Vector2 Knight::GetMoveDir()
	{
		int idx = 0;
		float minDist = 50;
		Vector2 playerPos = MapManager::GetPlayerIndex();
		for (int i = 0; i < ((int)AttackDir::Size); i++)
		{
			Vector2 reslt = mIndex + _AttackDirections[i];
			if (!MapManager::IndexIsValid(reslt) 
				|| MapManager::GetEnemy(reslt) != nullptr
				|| MapManager::GetWall(reslt) != nullptr)
				continue;
			float dist = Vector2::Distance(playerPos, reslt);
			if (dist < minDist)
			{
				idx = i;
				minDist = dist;
			}
		}
		return _AttackDirections[idx];
	}
	void Knight::SetWeapon()
	{
		mWeapon = object::Instantiate<KnightWeapon>(GameObject::GetScene(), GameObject::mTransform, GameObject::mTransform->GetPos(), eLayerType::Effects);
		mWeapon->SetPower(mAttackPower);
	}
	Vector2 Knight::GetNextDir()
	{
		if (mBeatCount % mMoveBeat == 0)
		{
			Vector2 dir = GetPlayerAttackDir();
			if (dir != Vector2::Zero)
				return dir;
			else
				return GetMoveDir();
		}
		return Vector2::Zero;
	}
}