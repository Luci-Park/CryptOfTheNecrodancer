#pragma once
#include "LuciEngine.h"
namespace cl
{
	class Room
	{
	public:
		enum class WallType {Rectangle, Plus, Columns, Size};
		Room(int zone);
		virtual ~Room();

	protected:
		void SetWall(WallType wallType);
		std::vector<std::vector<eFloorTypes>> mFloors;
		std::vector<std::vector<eWallTypes>> mWalls;
		std::vector<std::vector<eMonsterTypes>> mMonsters;
		Vector2 mSize;
		Vector2 mMiddlePos;		
		int mZone;
	};
	class StartRoom : public Room
	{
	public:
		StartRoom(int zone);
		~StartRoom();
	};
	class RandomRoom : public Room
	{
	public:
		RandomRoom(int zone);
		~RandomRoom();
	};
}

