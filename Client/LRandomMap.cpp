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
		section[0][0] = 1;
		section[0][1] = 11;
		section[1][0] = 7;
		section[1][1] = 17;
		section[2][0] = 12;
		section[2][1] = 23;


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
				if (3 <= i && i < 20 && 3 <= j && j < 20)
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
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				mRooms[i][j] = nullptr;
			}
		}
		CreateExitRoom();

	}
	void RandomMap::CreateExitRoom()
	{
		int rand1 = GetRandomInt(0, 2);
		int rand2 = GetRandomInt(0, 1);
		int y = 2;
		int x = 2;
		if (rand2)
			y = rand1;
		else
			x = rand1;
		mRooms[y][x] = new ExitRoom(mZone);
		SetRoom(y, x);
	}
	void RandomMap::CreateStartRoom()
	{
	}
	void RandomMap::SetRoom(int sectionY, int sectionX)
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
				Vector2 l1 = mRooms[i]->mOffset;
				Vector2 r1 = l1 + mRooms[i]->mSize + Vector2::One;
				Vector2 l2 = Vector2(randx, randy);
				Vector2 r2 = l2 + mRooms[idx]->mSize + Vector2::One;
				if (DoesRoomOverlap(l1, r1, l2, r2))
				{
					overlap = true;
					break;
				}
			}
		} while (overlap);
		mRooms[idx]->mOffset = Vector2(randx, randy);
	}
	void RandomMap::CopyRooms()
	{
		for (int i = 0; i < 2; ++i)
		{
			if (mRooms[i] != nullptr);
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
				if (mMonsterBluePrint[i + startPos.y][j + startPos.x] != eMonsterTypes::None)
				{
					int y = i + startPos.y;
					int x = j + startPos.x;
				}
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
	bool RandomMap::DoesRoomOverlap(Vector2 l1, Vector2 r1, Vector2 l2, Vector2 r2)
	{
		// if rectangle has area 0, no overlap
		if (l1.x == r1.x || l1.y == r1.y || r2.x == l2.x || l2.y == r2.y)
			return false;

		// If one rectangle is on left side of other
		if (l1.x > r2.x || l2.x > r1.x)
			return false;

		// If one rectangle is above other
		if (r1.y < l2.y || r2.y < l1.y)
			return false;

		return true;
	}
}