#include "LRandomMap.h"
#include "LRoom.h"
namespace cl
{
	RandomMap::RandomMap()
	{
	}
	RandomMap::~RandomMap()
	{
	}
	void RandomMap::CreateMapBluePrint()
	{
		Room* room = new RandomRoom(1);
		mMapSize = room->mSize;
		Map::Initialize(mMapSize);
		CopyRoom(Vector2::Zero, room);
		mPlayerIndex = room->mMiddlePos;
		delete room;
	}
	void RandomMap::CopyRoom(Vector2 startPos, Room* room)
	{
		for (int i = 0; i < room->mSize.y; ++i)
		{
			for (int j = 0; j < room->mSize.x; ++j)
			{
				mWallBluePrint[i + startPos.y][j + startPos.x] = room->mWalls[i][j];
				mFloorBluePrint[i + startPos.y][j + startPos.x] = room->mFloors[i][j];
				mMonsterBluePrint[i + startPos.y][j + startPos.x] = room->mMonsters[i][j];
			}
		}
		for (int i = 0; i < room->mLights.size(); i++)
			mLightPos.push_back(room->mLights[i]);
	}
}