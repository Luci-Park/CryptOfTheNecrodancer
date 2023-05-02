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
		mMapSize = Vector2(MAPSIZE, MAPSIZE);
		Map::Initialize(mMapSize);
		InitializeWall();
		CreateRoom();
		CopyRooms();
		CreateCorridor();
		DeleteRooms();
	}
	void RandomMap::InitializeWall()
	{
		for (int i = 0; i < mMapSize.y; i++)
		{
			for (int j = 0; j < mMapSize.x; j++)
			{
				if (MARGIN <= i && i <= MAPSIZE - MARGIN
					&& MARGIN <= j && j <= MAPSIZE - MARGIN)
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
		CreateRooms(nullptr);
	}
	void RandomMap::CreateRooms(Room* parent)
	{
		bool set = false;
		if (mRooms.size() >= 6)
			return;
		Room* newRoom = nullptr;
		if (mRooms.size() == 0)
		{			
			newRoom = new RandomRoom(mZone);
			int y = MAPSIZE - 2 - newRoom->mSize.y;
			int x = MAPSIZE - 2 - newRoom->mSize.x;
			if (GetRandomInt(0, 1))
				y = GetRandomInt(1, y);
			else
				x = GetRandomInt(1, x);
			newRoom->mOffset = { x, y };
			set = true;
		}
		else
		{
			if (mRooms.size() == STARTIDX)
				newRoom = new StartRoom(mZone);
			else
				newRoom = new RandomRoom(mZone);
			while (!set && parent != nullptr)
			{
				std::vector<Vector2> v = { Vector2::Left, Vector2::Right, Vector2::Up, Vector2::Down };
				std::shuffle(v.begin(), v.end(), std::default_random_engine());
				for (int i = 0; i < 4; ++i)
				{
					if (IsDirPossible(v[i], parent, newRoom))
					{
						parent->mChildren[Room::GetIndexFromDirection(v[i])] = newRoom;
						newRoom->mParent = parent;
						set = true;
						break;
					}
				}
				if (!set)
				{
					parent = parent->mParent;
				}
			}
			if (!set)
			{
				for (int i = 1; i < mRooms.size(); ++i)
				{
					parent = mRooms[i];
					std::vector<Vector2> v = { Vector2::Left, Vector2::Right, Vector2::Up, Vector2::Down };
					std::shuffle(v.begin(), v.end(), std::default_random_engine());
					for (int i = 0; i < 4; ++i)
					{
						if (IsDirPossible(v[i], parent, newRoom))
						{
							parent->mChildren[Room::GetIndexFromDirection(v[i])] = newRoom;
							newRoom->mParent = parent;
							set = true;
							break;
						}
					}
					if (set) break;
				}
			}
		}
		if (set && newRoom != nullptr)
		{
			mRooms.push_back(newRoom);
			CreateRooms(newRoom);
		}
		if (!set && newRoom != nullptr)
			delete newRoom;
	}
	bool RandomMap::IsDirPossible(Vector2 dir, Room* parent, Room* child)
	{
		if (parent->mChildren[Room::GetIndexFromDirection(dir)] != nullptr)
			return false;
		if (dir == Vector2::Left)
		{
			int x = parent->mOffset.x - 1;
			x -=child->mSize.x;
			if (x < 1)
				return false;
			if (x >= 2)
				x -= GetRandomInt(0, 1);
			return SetRoomY(x, parent, child);
		}
		else if (dir == Vector2::Right)
		{
			int x = parent->mOffset.x + parent->mSize.x + 1;
			if (x +child->mSize.x >= MAPSIZE - 1)
				return false;
			if (x +child->mSize.x <= MAPSIZE - 3)
				x += GetRandomInt(0, 1);
			return SetRoomY(x, parent, child);
		}
		else if (dir == Vector2::Up)
		{
			int y = parent->mOffset.y - 1;
			y -=child->mSize.y;
			if (y < 1)
				return false;
			if (y >= 2)
				y -= GetRandomInt(0, 1);
			return SetRoomX(y, parent, child);
		}
		else if (dir == Vector2::Down)
		{
			int y = parent->mOffset.y + parent->mSize.y + 1;
			if (y +child->mSize.y >= MAPSIZE - 1)
				return false;
			if (y +child->mSize.y <= MAPSIZE - 3)
				y += GetRandomInt(0, 1);
			return SetRoomX(y, parent, child);
		}
	}
	bool RandomMap::SetRoomY(int x, Room* parent, Room* child)
	{
		int min =parent->mOffset.y -child->mSize.y;
		int max =parent->mOffset.y +parent->mSize.y;
		if (max +child->mSize.y >= MAPSIZE - 1)
			max = MAPSIZE - 2 -child->mSize.y;
		if (min <= 0)
			min = 1;
		for (int i = 0; i < mRooms.size(); i++)
		{
			while (DoesRoomOverlap(
				mRooms[i]->mOffset, mRooms[i]->mOffset + mRooms[i]->mSize
				, Vector2(x, min), Vector2(x, min) +child->mSize)
				&& min <= max)
			{
				min++;
			}
			while (DoesRoomOverlap(
				mRooms[i]->mOffset, mRooms[i]->mOffset + mRooms[i]->mSize
				, Vector2(x, max), Vector2(x, max) +child->mSize)
				&& min <= max)
			{
				max--;
			}
			if (max < min)
				return false;
		}
		int y = GetRandomInt(min, max);
		child->mOffset = Vector2(x, y);
		return true;
	}
	bool RandomMap::SetRoomX(int y, Room* parent, Room* child)
	{
		int min =parent->mOffset.x -child->mSize.x;
		int max =parent->mOffset.x +parent->mSize.x;
		if (max +child->mSize.x >= MAPSIZE -1)
			max = MAPSIZE - 2 -child->mSize.x;
		if (min <= 0)
			min = 1;
		for (int i = 0; i < mRooms.size(); i++)
		{
			while (DoesRoomOverlap(
				mRooms[i]->mOffset, mRooms[i]->mOffset + mRooms[i]->mSize
				, Vector2(min, y), Vector2(min, y) +child->mSize)
				&& min <= max)
			{
				min++;
			}
			while (DoesRoomOverlap(
				mRooms[i]->mOffset, mRooms[i]->mOffset + mRooms[i]->mSize
				, Vector2(max, y), Vector2(max, y) +child->mSize)
				&& min <= max)
			{
				max--;
			}
			if (max < min)
				return false;
		}
		int x = GetRandomInt(min, max);
		child->mOffset = Vector2(x, y);
		return true;
	}

	void RandomMap::CopyRooms()
	{
		for (int i = 0; i < mRooms.size(); ++i)
		{
			CopyRoom(mRooms[i]);
			if (i == STARTIDX)
				mPlayerIndex = mRooms[i]->mCenter + mRooms[i]->mOffset;
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
	void RandomMap::CreateCorridor()
	{
		for (int i = 0; i < mRooms.size(); ++i)
		{
			Room* room = mRooms[i];
			for (int j = 0; j < room->mChildren.size(); j++)
			{
				if (room->mChildren[j] != nullptr)
					CreateCorridor(room, room->mChildren[j], Room::GetDirectionFromIndex(j));
			}
		}
	}
	void RandomMap::CreateCorridor(Room* parent, Room* child, Vector2 dir)
	{
		Vector2 parentCenter = parent->mOffset + parent->mCenter;
		Vector2 childCenter = child->mOffset + child->mCenter;
		Vector2 parentDoor, childDoor;
		if (dir == Vector2::Left || dir == Vector2::Right)
		{
			if (dir == Vector2::Left)
			{
				parentDoor.x = parent->mOffset.x;
				childDoor.x = child->mOffset.x + child->mSize.x - 1;
			}
			else
			{
				parentDoor.x = parent->mOffset.x + parent->mSize.x - 1;
				childDoor.x = child->mOffset.x;				
			}

			if (parentCenter.y < childCenter.y)
			{
				parentDoor.y = parent->mOffset.y + parent->mSize.y - 3;
				childDoor.y = child->mOffset.y + 2;
			}
			else
			{
				parentDoor.y = parent->mOffset.y + 2;
				childDoor.y = child->mOffset.y + child->mSize.y - 3;
			}
		}
		else{
			if (dir == Vector2::Up)
			{
				parentDoor.y = parent->mOffset.y;
				childDoor.y = child->mOffset.y + child->mSize.y - 1;
			}
			else
			{
				parentDoor.y = parent->mOffset.y + parent->mSize.y - 1;
				childDoor.y = child->mOffset.y;
			}

			if (parentCenter.x < childCenter.x)
			{
				parentDoor.x = parent->mOffset.x + parent->mSize.x - 3;
				childDoor.x = child->mOffset.x + 2;
			}
			else
			{
				parentDoor.x = parent->mOffset.x + 2;
				childDoor.x = child->mOffset.x + child->mSize.x - 3;
			}
		}
		int cursorX = parentDoor.x;
		int cursorY = parentDoor.y;
		int sX = (childDoor.x > parentDoor.x) ? 1 : -1;
		int sY = (childDoor.y > parentDoor.y) ? 1 : -1;
		while (cursorX != childDoor.x || cursorY != childDoor.y)
		{
			int xDiff = abs(childDoor.x - cursorX);
			int yDiff = abs(childDoor.y - cursorY);
			if (xDiff > 0 && yDiff > 0)
			{
				if (GetRandomInt(0, 1))
					cursorX += sX;
				else
					cursorY += sY;
			}
			else if (xDiff > 0)
				cursorX += sX;
			else if (yDiff > 0)
				cursorY += sY;
			mWallBluePrint[cursorY][cursorX] = eWallTypes::None;
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