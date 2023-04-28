#include "LRoom.h"
#define MINROOMSIZE 6
#define MAXROOMSIZE 9
namespace cl
{
	Room::Room(int zone)
		: mZone(zone)
	{
	}
	Room::~Room()
	{
	}
	void Room::SetWall(WallType wallType)
	{
		mWalls.resize(mSize.y);
		for (int i = 0; i < mSize.y; ++i)
		{
			mWalls[i].resize(mSize.x);
			for (int j = 0; j < mSize.x; ++j)
			{
				mWalls[i][j] = eWallTypes::None;
				if (i == 0 || i == mSize.y - 1 || j == 0 || j == mSize.x -1)
				{
					mWalls[i][j] = eWallTypes::DirtWall;
				}
			}
		}
		if (wallType == WallType::Plus)
		{
			mWalls[1][1] = eWallTypes::DirtWall;
			mWalls[1][mSize.x - 2] = eWallTypes::DirtWall;
			mWalls[mSize.y - 2][1] = eWallTypes::DirtWall;
			mWalls[mSize.y - 2][mSize.x - 2] = eWallTypes::DirtWall;
		}
		else if (wallType == WallType::Columns)
		{
			mWalls[2][2] = eWallTypes::DirtWall;
			mWalls[2][mSize.x - 3] = eWallTypes::DirtWall;
			mWalls[mSize.y - 3][2] = eWallTypes::DirtWall;
			mWalls[mSize.y - 3][mSize.x - 3] = eWallTypes::DirtWall;
		}
	}
	StartRoom::StartRoom(int zone)
		: Room(zone)
	{
		mSize = Vector2(7, 7);
		mMiddlePos = Vector2(3, 3);
		SetWall(WallType::Rectangle);
	}
	StartRoom::~StartRoom()
	{
	}
	RandomRoom::RandomRoom(int zone)
		: Room(zone)
	{
		mSize.x = GetRandomInt(MINROOMSIZE, MAXROOMSIZE);
		mSize.y = GetRandomInt(MINROOMSIZE, MAXROOMSIZE);
		mMiddlePos.x = (int)(mSize.x * 0.5);
		mMiddlePos.y = (int)(mSize.y * 0.5);
		SetWall((WallType)GetRandomInt(0, (int)WallType::Size));
	}
	RandomRoom::~RandomRoom()
	{
	}
}