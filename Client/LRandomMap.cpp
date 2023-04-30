#include "LRandomMap.h"
#include "LRoom.h"
#include "LSceneManager.h"
namespace cl
{
	RandomMap::RandomMap()
	{
		eSceneType currentScene = SceneManager::GetActiveScene()->GetSceneType();
		if (currentScene == eSceneType::Depth1)
			mZone = 1;
		else if (currentScene == eSceneType::Depth2)
			mZone = 2;
		else if (currentScene == eSceneType::Depth3)
			mZone = 3;
		else
			mZone = 1;
	}
	RandomMap::~RandomMap()
	{
	}
	void RandomMap::CreateMapBluePrint()
	{
		mMapSize = Vector2(25, 25);
		Map::Initialize(mMapSize);
		InitializeWall();
		CreateRoom();
		CopyRooms();
		mPlayerIndex = mRooms[1]->mMiddlePos + mRooms[1]->mOffset;
		DeleteRooms();
	}
	void RandomMap::InitializeWall()
	{
		for (int i = 0; i < 25; i++)
		{
			for (int j = 0; j < 25; j++)
			{
				if (5 <= i && i < 20 && 5 <= j && j < 20)
				{
					mWallBluePrint[i][j] = Room::GetRandomDirtWall();
				}
				else
				{
					mWallBluePrint[i][j] = eWallTypes::Border;
				}
			}
		}
	}
	void RandomMap::CreateRoom()
	{
		mRooms.resize(6);
		mRooms[0] = new ExitRoom(mZone);
		SetRoom(0);
		mRooms[1] = new StartRoom(mZone);
		SetRoom(1);
		for (int i = 2; i < 6; i++)
		{
			mRooms[i] = new RandomRoom(mZone);
			SetRoom(i);
		}
	}
	void RandomMap::SetRoom(int idx)
	{
		bool overlap;
		int randy, randx;
		do
		{
			overlap = false;
			randy = GetRandomInt(1, 24-mRooms[idx]->mSize.y);
			randx = GetRandomInt(1, 24 - mRooms[idx]->mSize.x);
			for (int i = 0; i < idx; ++i)
			{
				int xLeft = mRooms[i]->mOffset.x;
				int xRight = mRooms[i]->mOffset.x + mRooms[i]->mSize.x - 1;
				int yTop = mRooms[i]->mOffset.y;
				int yBottom = mRooms[i]->mOffset.y + mRooms[i]->mSize.y - 1;
				if (xLeft <= randx && randx <= xRight
					&& yTop <= randy && randy <= yBottom)
				{
					overlap == true;
					break;
				}
			}
		} while (overlap);
		mRooms[idx]->mOffset = Vector2(randx, randy);
	}
	void RandomMap::CopyRooms()
	{
		for (int i = 0; i < 6; ++i)
		{
			CopyRoom(mRooms[i]);
		}
	}
	void RandomMap::CopyRoom(Room* room)
	{
		Vector2 startPos = room->mOffset;
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
			mLightPos.push_back(room->mLights[i] + room->mOffset);
		for (int i = 0; i < room->mStairPos.size(); i++)
		{
			room->mStairPos[i].first += room->mOffset;
			mStairPos.push_back(room->mStairPos[i]);
		}
	}
	void RandomMap::DeleteRooms()
	{
		for (int i = 0; i < 6; ++i)
		{
			delete mRooms[i];
			mRooms[i] = nullptr;
		}
	}
}