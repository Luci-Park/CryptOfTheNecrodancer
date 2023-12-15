#include "LRandomMap.h"
#include "LRoomBluePrint.h"
#include "LSceneManager.h"
#include "LFloorTile.h"
namespace cl
{
	RandomMap::RandomMap(int zone)
		: mZone(zone)
	{
	}
	RandomMap::~RandomMap()
	{
	}
	void RandomMap::OnKeyOpen()
	{
		Vector2 pos = mStairPos[0].first;
		StairTile* tile = dynamic_cast<StairTile*>(mFloor[pos.y][pos.x]);
		if (tile != nullptr)
			tile->SetLock(false);
		Map::OnKeyOpen();
	}
	void RandomMap::CreateMapBluePrint()
	{
		mMapSize = Vector2(MAPSIZE, MAPSIZE);
		Map::Initialize(mMapSize);
		InitializeWall();
		CreateRoomBluePrint();
		CopyRoomsToFullBluePrint();
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
					mWallBluePrint[i][j] = RoomBluePrint::GetRandomDirtWall();
				}
				else
				{
					mWallBluePrint[i][j] = eWallTypes::Border;
				}
			}
		}
	}
	void RandomMap::CreateRoomBluePrint()
	{
		CreateRoomBluePrint(nullptr);
	}
	void RandomMap::CreateRoomBluePrint(RoomBluePrint* parent)
	{
		bool set = false;
		if (mRooms.size() >= 6)
			return;
		RoomBluePrint* newRoom = nullptr;
		if (mRooms.size() == 0)
		{			
			newRoom = new ExitRoom(mZone);
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
						parent->mChildren[RoomBluePrint::GetIndexFromDirection(v[i])] = newRoom;
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
							parent->mChildren[RoomBluePrint::GetIndexFromDirection(v[i])] = newRoom;
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
			CreateRoomBluePrint(newRoom);
		}
		if (!set && newRoom != nullptr)
			delete newRoom;
	}
	bool RandomMap::IsDirPossible(Vector2 dir, RoomBluePrint* parent, RoomBluePrint* child)
	{
		if (parent->mChildren[RoomBluePrint::GetIndexFromDirection(dir)] != nullptr)
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
	bool RandomMap::SetRoomY(int x, RoomBluePrint* parent, RoomBluePrint* child)
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
	bool RandomMap::SetRoomX(int y, RoomBluePrint* parent, RoomBluePrint* child)
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

	void RandomMap::CopyRoomsToFullBluePrint()
	{
		for (int i = 0; i < mRooms.size(); ++i)
		{
			CopyRoom(mRooms[i]);
			if (i == STARTIDX)
			{
				mPlayerIndex = mRooms[i]->mCenter + mRooms[i]->mOffset;
				//mPlayerIndex = mStairPos[mStairPos.size() - 1].first + Vector2::Right;
			}
		}
	}
	void RandomMap::CopyRoom(RoomBluePrint* room)
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
	void RandomMap::CreateCorridor()
	{
		for (int i = 0; i < mRooms.size(); ++i)
		{
			RoomBluePrint* room = mRooms[i];
			for (int j = 0; j < room->mChildren.size(); j++)
			{
				if (room->mChildren[j] != nullptr)
					CreateCorridor(room, room->mChildren[j], RoomBluePrint::GetDirectionFromIndex(j));
			}
		}
	}
	void RandomMap::CreateCorridor(RoomBluePrint* parent, RoomBluePrint* child, Vector2 dir)
	{
		Vector2 parentCenter = parent->mOffset + parent->mCenter;
		Vector2 childCenter = child->mOffset + child->mCenter;
		int cursorX = parentCenter.x;
		int cursorY = parentCenter.y;
		int sX = (childCenter.x > parentCenter.x) ? 1 : -1;
		int sY = (childCenter.y > parentCenter.y) ? 1 : -1;
		int dx[] = { 0, 1, 0, -1, 1, 1, -1, -1 };
		int dy[] = { 1, 0, -1, 0, 1, -1, 1, -1 };
		while (!IsIndexInRoom({cursorX, cursorY}, child))
		{
			//if (IsOnBoundary({ cursorX, cursorY }, parent))
			//{
			//	if (mWallBluePrint[cursorY][cursorX - 1] != eWallTypes::None
			//		&& mWallBluePrint[cursorY][cursorX + 1] != eWallTypes::None)
			//	{
			//		mWallBluePrint[cursorY][cursorX] = eWallTypes::HorizontalDoor;
			//		cursorY += (childCenter.y > cursorY) ? 1 : -1;
			//	}
			//	else
			//	{
			//		mWallBluePrint[cursorY][cursorX] = eWallTypes::VerticalDoor;
			//		cursorX += (childCenter.x > cursorX) ? 1 : -1;
			//	}
			//}
			//else
			//{
				int xDiff = abs(childCenter.x - cursorX);
				int yDiff = abs(childCenter.y - cursorY);
				if (xDiff > 0 && yDiff > 0)
				{
					if (GetRandomInt(0, 1))
						cursorX += (childCenter.x > cursorX) ? 1 : -1;
					else
						cursorY += (childCenter.y > cursorY) ? 1 : -1;
				}
				else if (xDiff > 0)
					cursorX += (childCenter.x > cursorX) ? 1 : -1;
				else if (yDiff > 0)
					cursorY += (childCenter.y > cursorY) ? 1 : -1;
//			}
			if (!IsDigIndexValid({ cursorX, cursorY }))
				break;
			mWallBluePrint[cursorY][cursorX] = eWallTypes::None;
			for (int i = 0; i < 8; ++i)
			{
				Vector2 v = { cursorX + dx[i], cursorY + dy[i] };
				if (IsDigIndexValid(v) && mWallBluePrint[v.y][v.x] == eWallTypes::Border)
					mWallBluePrint[v.y][v.x] = RoomBluePrint::GetRandomDirtWall();
			}
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
	bool RandomMap::IsIndexInRoom(Vector2 pos, RoomBluePrint* room)
	{
		Vector2 r1 = room->mOffset + room->mSize - Vector2::Zero;
		if (room->mOffset.x < pos.x && pos.x < r1.x
			&& room->mOffset.y < pos.y && pos.y < r1.y)
			return true;
		return false;
	}
	bool RandomMap::IsOnBoundary(Vector2 pos, RoomBluePrint* room)
	{
		Vector2 r1 = room->mOffset + room->mSize - Vector2::One;
		if (pos.y == room->mOffset.y && room->mOffset.x < pos.x && pos.x < r1.x)
			return true;
		if (pos.y == r1.y && room->mOffset.x < pos.x && pos.x < r1.x)
			return true;
		if (pos.x == room->mOffset.x && room->mOffset.y < pos.y && pos.y < r1.y)
			return true;
		if (pos.x == r1.x && room->mOffset.y < pos.y && pos.y < r1.y)
			return true;
		return false;
	}
	bool RandomMap::IsDigIndexValid(Vector2 index)
	{
		if (0 < index.x && index.x < mMapSize.x - 1
			&& 0 < index.y && index.y < mMapSize.y - 1)
			return true;
		return false;
	}
}