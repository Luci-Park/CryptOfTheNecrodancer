#include "LBishop.h"
#include "LBishopSprite.h"
#include "LMapManager.h"
#include "LCadence.h"
namespace cl
{
	Bishop::Bishop(Scene* sc)
		: Pieces(sc)
	{
		mMoveBeat = 4;
	}
	Bishop::~Bishop()
	{
	}
	void Bishop::Initialize()
	{
		Monster::Initialize();
		mPieceSprite = object::Instantiate<BishopSprite>(GameObject::GetScene(), mTransform, mTransform->GetPos(), eLayerType::Monster);
		mSprite = mPieceSprite;
	}
	Vector2 Bishop::GetNextDir()
	{
		if (mBeatCount >= 0 && mBeatCount % mMoveBeat == 0)
		{
			Vector2 playerIndex = MapManager::GetPlayerIndex();
			Vector2 dir = (playerIndex - mIndex).TileNormalize();
			if (Vector2::IsDiagonal(dir))
				return dir;
			else
			{
				Vector2 prevPlayerPos = playerIndex - MapManager::GetPlayer(playerIndex)->GetInput();
				Vector2 prevDir = (prevPlayerPos - mIndex).TileNormalize();
				if (Vector2::IsDiagonal(prevDir))
					return prevDir;
				else
				{
					if (dir.y == 0)
						dir.y = 1;
					else if (dir.x == 0)
						dir.x = -1;
					return dir;
				}
			}
		}
		return Vector2::Zero;
	}
}
