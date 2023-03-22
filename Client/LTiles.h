#pragma once
#include "LMath.h"
#include "LSprite.h"
namespace cl
{
	enum eFloorSpriteTypes
	{
		DarkFloor1,
		DarkFloor2,
		DarkFloor3,
		DarkFloor4,
		LightFloor1,
		LightFloor2,
		LightFloor3,
		LightFloor4,
		GreenFlashFloor1,
		GreenFlashFloor2,
		RedFlashFloor1,
		RedFlashFloor2,
		Water1,
		Water2,
		Water3,
		ClosedStairs,
		OpenedStairs,
		Size
	};

	enum eWallSpriteTypes
	{
		Wall1,
		Wall2,
		Wall3,
		Wall4,
		Wall5,
		Wall6,
		Wall7,
		Wall8,
		Wall9,
		Wall10,
		Wall11,
		Wall12,
		Wall13,
		Wall14,
		Wall15,
		Wall16,
		HarderWall,
		StoneWall1,
		StoneWall2,
		BossWall1,
		BossWall2,
		BossWall3,
		BossWall4,
		BossWall5,
		GoldWall,
		Border1,
		Border2,
		Border3,
		Border4,
		Border5,
		Border6,
		Border7,
		Border8,
		DoorHorizontal,
		DoorVertical,
		Size
	};

	struct TileInfo
	{
		static const int tileUnit;
		static const Vector2 floorSpriteSize;
		static const Vector2 wallSpriteSize;
		static const float tileScale;
		static const Vector2 floorIndex[];
		static const Vector2 wallIndex[];

		static Sprite GetFloorTile(eFloorSpriteTypes tileType);
		static Sprite GetWallTile(eWallSpriteTypes tileType);
	};
}

