#pragma once
#include "LMath.h"
#include "LSprite.h"
namespace cl
{
	enum eFloorTypes
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

	struct TileInfo
	{
		static const int tileUnit;
		static const float tileScale;
		static const Vector2 floorIndex[];

		static Sprite GetFloorTile(eFloorTypes tileType);
	};
}

