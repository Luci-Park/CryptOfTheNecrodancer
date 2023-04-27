#include "LRoom.h"
#define MINROOMSIZE 6
#define MAXROOMSIZE 9
namespace cl
{
	Room::Room()
	{
	}
	Room::~Room()
	{
	}
	void Room::SetWall(WallType wallType)
	{
		mTiles.resize(mSize.y);
		for (int i = 0; i < mSize.y; ++i)
		{
			mTiles[i].resize(mSize.x);
			for (int j = 0; j < mSize.x; ++j)
			{
				mTiles[i][j] = TileObjects::None;
				if (i == 0 || i == mSize.y - 1 || j == 0 || j == mSize.x -1)
				{
					mTiles[i][j] = TileObjects::Wall;
				}
			}
		}
		if (wallType == WallType::Plus)
		{
			mTiles[1][1] = TileObjects::Wall;
			mTiles[1][mSize.x - 2] = TileObjects::Wall;
			mTiles[mSize.y - 2][1] = TileObjects::Wall;
			mTiles[mSize.y - 2][mSize.x - 2] = TileObjects::Wall;
		}
		else if (wallType == WallType::Columns)
		{
			mTiles[2][2] = TileObjects::Wall;
			mTiles[2][mSize.x - 3] = TileObjects::Wall;
			mTiles[mSize.y - 3][2] = TileObjects::Wall;
			mTiles[mSize.y - 3][mSize.x - 3] = TileObjects::Wall;
		}
	}
	StartRoom::StartRoom()
	{
		mSize = Vector2(7, 7);
		mMiddlePos = Vector2(3, 3);
		SetWall(WallType::Rectangle);
	}
	StartRoom::~StartRoom()
	{
	}
	RandomRoom::RandomRoom()
	{
		mSize.x = GetRandomInt(MINROOMSIZE, MAXROOMSIZE);
		mSize.y = GetRandomInt(MINROOMSIZE, MAXROOMSIZE);
		SetWall((WallType)GetRandomInt(0, (int)WallType::Size));
	}
	RandomRoom::~RandomRoom()
	{
	}
}