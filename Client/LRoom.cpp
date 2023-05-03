#include "LRoom.h"
#include "LMonsterFactory.h"
#define MINROOMSIZE 6
#define MAXROOMSIZE 9
namespace cl
{
	Room::Room(int zone)
		: mZone(zone)
	{
		mParent = nullptr;
		mChildren = std::vector<Room*>(4, nullptr);
	}
	Room::~Room()
	{
	}
	void Room::Reset()
	{
		mFloors = std::vector<std::vector<eFloorTypes>>(mSize.y, std::vector<eFloorTypes>(mSize.x, eFloorTypes::ActiveDirt));
		mWalls = std::vector<std::vector<eWallTypes>>(mSize.y, std::vector<eWallTypes>(mSize.x, eWallTypes::None));
		mMonsters = std::vector<std::vector<eMonsterTypes>>(mSize.y, std::vector<eMonsterTypes>(mSize.x, eMonsterTypes::None));
	}
	void Room::SetWall(eWallTypes type)
	{
		for (int i = 0; i < mSize.y; ++i)
		{
			for (int j = 0; j < mSize.x; ++j)
			{
				if (i == 0 || i == mSize.y - 1 || j == 0 || j == mSize.x -1)
				{
					if (eWallTypes::DirtWall == type) {
						mWalls[i][j] = GetRandomDirtWall();
					}
					else
					{
						mWalls[i][j] = type;
					}
				}
			}
		}
	}
	void Room::SetColumn(eWallTypes type)
	{
		if (mSize.x <= 6 || mSize.y <= 6) return;
		if (eWallTypes::None == type)return;
		
		eWallTypes types[4];
		for (int i = 0; i < 4; ++i)
			types[i] = type == eWallTypes::DirtWall ? GetRandomDirtWall() : type;
		
		mWalls[2][2] = types[0];
		mWalls[2][mSize.x - 3] = types	[1];
		mWalls[mSize.y - 3][2] = types[2];
		mWalls[mSize.y - 3][mSize.x - 3] = types[3];
	}
	void Room::SetCorner(eWallTypes type)
	{
		if (eWallTypes::None == type) return;
		eWallTypes types[4];
		for (int i = 0; i < 4; ++i)
			types[i] = type == eWallTypes::DirtWall ? GetRandomDirtWall() : type;

		mWalls[1][1] = types[0];
		mWalls[1][mSize.x - 2] = types[1];
		mWalls[mSize.y - 2][1] = types[2];
		mWalls[mSize.y - 2][mSize.x - 2] = types[3];
	}
	void Room::SetLights(int numbers)
	{
		bool light[4] = { false, false, false, false };
		for (int i = 0; i < numbers; ++i)
		{
			int idx;
			do
			{
				idx = GetRandomInt(0, 3);
			} while (light[idx]);
			light[idx] = true;
			if (idx == 0)
				mLights.push_back(Vector2(GetRandomInt(1, mSize.x - 2), 0));
			else if (idx == 1)
				mLights.push_back(Vector2(GetRandomInt(1, mSize.x - 2), (int)mSize.y - 1));
			else if (idx == 2)
				mLights.push_back(Vector2(0, GetRandomInt(1, mSize.y - 2)));
			else
				mLights.push_back(Vector2((int)mSize.x -1, GetRandomInt(1, mSize.y - 2)));
		}
	}
	int Room::GetIndexFromDirection(Vector2 dir)
	{
		if (dir == Vector2::Left)
			return 0;
		if (dir == Vector2::Right)
			return 1;
		if (dir == Vector2::Up)
			return 2;
		return 3;
	}
	Vector2 Room::GetDirectionFromIndex(int idx)
	{
		if (idx == 0) return Vector2::Left;
		if (idx == 1) return Vector2::Right;
		if (idx == 2) return Vector2::Up;
		return Vector2::Down;
	}
	eWallTypes Room::GetRandomDirtWall()
	{
		int rand = GetRandomInt(1, 10);
		return rand < 9 ? eWallTypes::DirtWall : eWallTypes::StoneWall;
	}
	StartRoom::StartRoom(int zone)
		: Room(zone)
	{
		mSize = Vector2(7, 7);
		Reset();
		mCenter = Vector2(3, 3);
		SetWall(eWallTypes::DirtWall);
		SetLights(GetRandomInt(1, 3));
	}
	StartRoom::~StartRoom()
	{
	}
	RandomRoom::RandomRoom(int zone)
		: Room(zone)
	{
		mSize.x = GetRandomInt(MINROOMSIZE, MAXROOMSIZE);
		mSize.y = GetRandomInt(MINROOMSIZE, MAXROOMSIZE);
		SetRoom();
	}
	RandomRoom::RandomRoom(int zone, int XMaxSize, int YMaxSize)
		:Room(zone)
	{
		int maxRoomX = XMaxSize < MAXROOMSIZE ? XMaxSize : MAXROOMSIZE;
		int maxRoomY = YMaxSize < MAXROOMSIZE ? YMaxSize : MAXROOMSIZE;
		mSize.x = GetRandomInt(MINROOMSIZE, maxRoomX);
		mSize.y = GetRandomInt(MINROOMSIZE, maxRoomY);
		SetRoom();
	}
	RandomRoom::~RandomRoom()
	{
	}
	void RandomRoom::SetRoom()
	{
		mCenter = mSize * 0.5;
		mCenter.x = (int)(mSize.x * 0.5);
		mCenter.y = (int)(mSize.y * 0.5);
		Reset();
		if (mZone >= 2 && GetRandomInt(1, 10) <= 1)
			CreateCatacombRoom();
		else
			CreateDirtRoom();
		SetLights(GetRandomInt(0, 3));
		CreateMonsters();
	}
	void RandomRoom::CreateCatacombRoom()
	{
		SetWall(eWallTypes::CatacombWall);
		SetColumn(eWallTypes::CatacombWall);
	}
	void RandomRoom::CreateDirtRoom()
	{
		SetWall(eWallTypes::DirtWall);
		int rand = GetRandomInt(1, 10);
		if (rand <= 1)
			SetColumn(eWallTypes::StoneWall);
		else if (rand <= 2)
			SetColumn(eWallTypes::DirtWall);
		else if (rand <= 6)
			SetCorner(eWallTypes::DirtWall);
	}
	void RandomRoom::CreateRandomFloors()
	{
		int rand = GetRandomInt(1, 10);
		if (rand > 1)
			return;
		for (int i = 0; i < mSize.y; ++i)
		{
			for (int j = 0; j < mSize.x; ++j)
			{
				if (mWalls[i][j] != eWallTypes::None) continue;
				rand = GetRandomInt(1, 5);
				if (rand == 1)
					mFloors[i][j] = eFloorTypes::Water;
			}
		}
	}
	void RandomRoom::CreateMonsters()
	{
		int rand = GetRandomInt(3, 6);
		for (int i = 0; i < rand; ++i)
		{
			while (true)
			{
				int randx = GetRandomInt(1, mSize.x - 2);
				int randy = GetRandomInt(1, mSize.y - 2);
				if (mWalls[randy][randx] == eWallTypes::None
					&& mMonsters[randy][randx] == eMonsterTypes::None)
				{
					mMonsters[randy][randx] = MonsterFactory::GetRandomMonster(mZone);
					break;
				}
			}
		}
	}
	ExitRoom::ExitRoom(int zone)
		:RandomRoom(zone)
	{
		AddStairs();
		AddBoss();
	}
	ExitRoom::ExitRoom(int zone, int XMaxSize, int YMaxSize)
		:RandomRoom(zone, XMaxSize, YMaxSize)
	{
	}
	ExitRoom::~ExitRoom()
	{
	}
	void ExitRoom::AddStairs()
	{
		while (true)
		{
			int randx = GetRandomInt(1, mSize.x - 2);
			int randy = GetRandomInt(1, mSize.y - 2);
			if (mWalls[randy][randx] == eWallTypes::None
				&& mMonsters[randy][randx] == eMonsterTypes::None)
			{
				mFloors[randy][randx] = eFloorTypes::OpenedStairs;
				mStairPos.push_back(std::make_pair(Vector2(randx, randy), eSceneType((int)eSceneType::Depth1 + mZone)));
				break;
			}
		}

	}
	void ExitRoom::AddBoss()
	{
		while (true)
		{
			int randx = GetRandomInt(1, mSize.x - 2);
			int randy = GetRandomInt(1, mSize.y - 2);
			if (mWalls[randy][randx] == eWallTypes::None
				&& mMonsters[randy][randx] == eMonsterTypes::None)
			{
				mMonsters[randy][randx] = MonsterFactory::GetRandomMiniBoss(mZone);
				break;
			}
		}
	}
}