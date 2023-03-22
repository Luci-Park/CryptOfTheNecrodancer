#include "LTiles.h"
namespace cl
{
	const int TileInfo::tileUnit = 24;
	const Vector2 TileInfo::floorSpriteSize = Vector2(27.0f, 27.0f);
	const Vector2 TileInfo::wallSpriteSize = Vector2(24.0f, 48.0f);
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
	const Vector2 TileInfo::wallIndex[eWallTypes::Size] = {
		Vector2(0, 0), //Wall1,
		Vector2(0, 1), //Wall2,
		Vector2(0, 2), //Wall3,
		Vector2(0, 3), //Wall4,
		Vector2(0, 4), //Wall5,
		Vector2(0, 5), //Wall6,
		Vector2(0, 6), //Wall7,
		Vector2(0, 7), //Wall8,
		Vector2(0, 8), //Wall9,
		Vector2(0, 9), //Wall10,
		Vector2(0, 10), //Wall11,
		Vector2(0, 11), //Wall12,
		Vector2(0, 12), //Wall13,
		Vector2(0, 13), //Wall14,
		Vector2(0, 14), //Wall15,
		Vector2(0, 15),	//Wall16,
		Vector2(0, 29), //HarderWall,
		Vector2(0, 31), //StoneWall1,
		Vector2(0, 32), //StoneWall2,
		Vector2(0, 34), //BossWall1,
		Vector2(0, 35), //BossWall2,
		Vector2(0, 36), //BossWall3,
		Vector2(0, 37), //BossWall4,
		Vector2(0, 38), //BossWall5,
		Vector2(6, 0), //GoldWall,
		Vector2(6, 4), //Border1,
		Vector2(6, 5), //Border2,
		Vector2(6, 6), //Border3,
		Vector2(6, 7), //Border4,
		Vector2(6, 8), //Border5,
		Vector2(6, 9), //Border6,
		Vector2(6, 10), //Border7,
		Vector2(6, 11), //Border8,
		Vector2(6, 12), // DoorHorizonal,
		Vector2(6, 13), // DoorVertical
	};

	Sprite TileInfo::GetFloorTile(eFloorTypes tileType)
	{
		Sprite sprite;
		Vector2 index = floorIndex[(int)tileType];
		sprite.leftTop.x = index.x * floorSpriteSize.x;
		sprite.leftTop.y = index.y * floorSpriteSize.y;
		sprite.size = floorSpriteSize;
		sprite.offset -= sprite.size * 0.5;
		return sprite;
	}

	Sprite TileInfo::GetWallTile(eWallTypes tileType)
	{
		Sprite sprite;
		Vector2 index = wallIndex[(int)tileType];
		sprite.leftTop.x = index.x * wallSpriteSize.x;
		sprite.leftTop.y = index.y * wallSpriteSize.y;
		sprite.size = wallSpriteSize;
		sprite.offset -= sprite.size * 0.5;
		return sprite;
	}
}