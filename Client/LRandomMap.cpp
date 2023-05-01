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
		mMapSize = Vector2(30, 30);
		Map::Initialize(mMapSize);
		InitializeWall();
		CreateRoom();
		CopyRooms();
		DeleteRooms();
	}
	void RandomMap::InitializeWall()
	{
		for (int i = 0; i < mMapSize.y; i++)
		{
			for (int j = 0; j < mMapSize.x; j++)
			{
				if (10 <= i && i <= 20 && 10 <= j && j <= 20)
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
		mRooms = std::vector<Room*>(6, nullptr);
		CreateRooms(0);
	}
	void RandomMap::CreateRooms(int idx)
	{
		if (idx == 0)
		{
			mRooms[idx] = new RandomRoom(mZone);
			int y = GetRandomInt(20, 29 - mRooms[idx]->mSize.y);
			int x = GetRandomInt(20, 29 - mRooms[idx]->mSize.x);
			mRooms[idx]->mOffset = { x, y };
		}
		else
		{
			if (idx == 4)
				mRooms[idx] = new StartRoom(mZone);
			std::vector<Vector2> v = { Vector2::Left, Vector2::Right, Vector2::Up, Vector2::Down };
			std::shuffle(v.begin(), v.end(), std::default_random_engine());
			for (int i = 0; i < 4; ++i)
			{
				if (IsDirPossible(v[i], idx))
				{
					mDirections.push_back(v[i]);
					break;
				}
			}
			
		}
		CreateRooms(idx + 1);
	}
	bool RandomMap::IsDirPossible(Vector2 dir, int idx)
	{
		if (dir == Vector2::Left)
		{
			int x = mRooms[idx - 1]->mOffset.x - 1;
			if (x - mRooms[idx]->mSize.x < 1)
				return false;
			int max = (std::min)(mRooms[idx - 1]->mOffset.y + 1, 29 - mRooms[idx]->mSize.y);
			int min =  mRooms[idx - 1]->mOffset.y + mRooms[idx - 1]->mSize.y - 1;
			if (min > max)
			{
				int t = min;
				min = max;
				max = t;
			}
			for (int i = 0; i < idx; ++i)
			{

			}

		}
	}
	void RandomMap::CopyRooms()
	{
		for (int i = 0; i < mRooms.size(); ++i)
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
		for (int i = 0; i < mRooms.size(); ++i)
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