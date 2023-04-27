#pragma once
#include "CommonInclude.h"
#include "LMath.h"
namespace cl
{
	struct Room
	{
	public:
		enum class TileObjects { Wall, Monster, Item, Crate, None };
		enum class WallType {Rectangle, Plus, Columns, Size};
		Room();
		~Room();
		void SetWall(WallType wallType);
		std::vector<std::vector<TileObjects>> mTiles;
		Vector2 mSize;
		Vector2 mMiddlePos;		
	};
	struct StartRoom : public Room
	{
	public:
		StartRoom();
		~StartRoom();
	};
	struct RandomRoom : public Room
	{
	public:
		RandomRoom();
		~RandomRoom();
	};
}

