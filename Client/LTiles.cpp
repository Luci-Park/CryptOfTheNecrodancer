#include "LTiles.h"
namespace cl
{
	const int TileInfo::tileUnit = 27;
	const float TileInfo::tileScale = 2.0f;
	const Vector2 TileInfo::floorIndex[eFloorTypes::Size] = {
		Vector2(0, 0), // DarkFloor1
		Vector2(0, 3), // DarkFloor2
		Vector2(1, 0), // DarkFloor3
		Vector2(1, 3), // DarkFloor4
		Vector2(0, 1), // LightFloor1
		Vector2(0, 2), // LightFloor2
		Vector2(0, 4), // LightFloor3
		Vector2(0, 5), // LightFloor4
		Vector2(1, 1), // GreenFlashFloor1
		Vector2(1, 4), // GreenFlashFloor2
		Vector2(1, 2), // RedFlashFloor1
		Vector2(1, 5), // ReadFlashFloor2
		Vector2(4, 6), // Water1
		Vector2(4, 7), // Water2
		Vector2(4, 8), // Water3
		Vector2(2, 8),// ClosedStairs
		Vector2(2, 6)// OpenedStairs
	};

	Sprite TileInfo::GetFloorTile(eFloorTypes tileType)
	{
		Sprite sprite;
		Vector2 index = floorIndex[(int)tileType];
		sprite.leftTop = index * tileUnit;
		sprite.size.x = tileUnit;
		sprite.size.y = tileUnit;
		sprite.offset -= sprite.size * 0.5;
		return sprite;
	}
}