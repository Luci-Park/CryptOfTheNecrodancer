#include "LRook.h"
#include "LRookSprite.h"
#include "LMapManager.h"
#include "LCadence.h"
namespace cl
{
	Rook::Rook(Scene* sc)
		:Pieces(sc)
	{
		mMoveBeat = 2;
	}
	Rook::~Rook()
	{
	}
	void Rook::Initialize()
	{
		Monster::Initialize();
		mPieceSprite = object::Instantiate<RookSprite>(GameObject::GetScene(), mTransform, mTransform->GetPos(), eLayerType::Monster);
		mSprite = mPieceSprite;
	}
	Vector2 Rook::GetNextDir()
	{
		if (mBeatCount >= 0 && mBeatCount % mMoveBeat == 0)
		{
			Vector2 playerIndex = MapManager::GetPlayerIndex();
			Vector2 dir = (playerIndex - mIndex).TileNormalize();
			if (Vector2::IsCardinal(dir))
				return dir;
			else
			{
				Vector2 prevPlayerPos = MapManager::GetPlayer()->GetPrevPos();
				Vector2 prevDir = (prevPlayerPos - mIndex).TileNormalize();
				if (Vector2::IsCardinal(prevDir))
					return prevDir;
				else
				{
					int yDiff = abs(playerIndex.y - mIndex.y);
					int xDiff = abs(playerIndex.x - mIndex.x);
					if (yDiff < xDiff)
						dir.x = 0;
					else
						dir.y = 0;
					return dir;
				}
			}
		}
		return Vector2::Zero;
	}
}