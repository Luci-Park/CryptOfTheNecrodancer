#include "LFloorStrategy.h"
#include "LFloorTile.h"
namespace cl
{
	FloorStrategy::FloorStrategy(FloorTile* tile)
	{
		mTile = tile;
		Vector2 index = tile->GetIndex();
		if (((int)index.y % 2 == 0 && (int)index.x % 2 == 0) || ((int)index.y % 2 == 1 && (int)index.x % 2 == 1))
			mIsLightTile = true;
	}
	LobbyStrategy::LobbyStrategy(FloorTile* tile)
		:FloorStrategy(tile)
	{
		if (mIsLightTile)
			mSprite = FloorTile::GetFloorSprite(FloorTile::eSpriteCategories::LightFloor);
		else
			mSprite = FloorTile::GetFloorSprite(FloorTile::eSpriteCategories::DarkFloor);
	}
}