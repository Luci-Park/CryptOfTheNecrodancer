#include "LFloorStrategy.h"
#include "LFloorTile.h"
namespace cl
{
	FloorStrategy::FloorStrategy(FloorTile* tile)
	{
		mTile = tile;
		Vector2 index = tile->GetIndex();
		int num = index.x + index.y + 2;
		mIsEvenPos = num % 2 == 0;
	}
	LobbyStrategy::LobbyStrategy(FloorTile* tile)
		:FloorStrategy(tile)
	{
		if (mIsEvenPos)
			mSprite = FloorTile::GetFloorSprite(FloorTile::eSpriteCategories::DarkFloor);
		else
			mSprite = FloorTile::GetFloorSprite(FloorTile::eSpriteCategories::LightFloor);
	}
}