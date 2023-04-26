#include "LPawn.h"
#include "LPawnSprite.h"
#include "LMapManager.h"
#include "LQueen.h"
namespace cl
{
	Pawn::Pawn(Scene* sc)
		:Pieces(sc)
	{
		mMoveBeat = 8;
	}
	Pawn::~Pawn()
	{
	}
	void Pawn::Initialize()
	{
		Monster::Initialize();
		mPieceSprite = object::Instantiate<PawnSprite>(GameObject::GetScene(), mTransform, mTransform->GetPos(), eLayerType::Monster);
		mSprite = mPieceSprite;
	}
	Vector2 Pawn::GetNextDir()
	{
		if (mBeatCount == 0 && MapManager::GetTileObject(mIndex + Vector2::Down * 2) == nullptr)
			return Vector2::Down * 2;
		else if (mBeatCount % mMoveBeat == 0)
		{
			if (MapManager::GetPlayer(mIndex + Vector2::DownLeft) != nullptr)
				return Vector2::DownLeft;
			else if (MapManager::GetPlayer(mIndex + Vector2::DownRight) != nullptr)
				return Vector2::DownRight;
			else if (MapManager::GetTileObject(mIndex + Vector2::Down) == nullptr)
				return Vector2::Down;
		}
		return Vector2::Zero;
	}
}
