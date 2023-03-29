#include "LMap.h"
#include "LObject.h"
#include "LGameManager.h"
namespace cl
{
#pragma region Parent - Map Class
	Map::Map()
	{
	}

	Map::~Map()
	{
		for (int i = 0; i < size.y; ++i)
			for (int j = 0; j < size.x; ++j)
				object::Destory(mFloor[i][j]);
	}
	
	void Map::CreateMap(Scene* sc)
	{
		CreateFloor(sc);
		CreateWall(sc);
	}

	void Map::CreateFloor(Scene* sc)
	{
		mFloor.resize(size.y);
		for (int i = 0; i < size.y; ++i)
		{
			mFloor[i].resize(size.x);
			for (int j = 0; j < size.x; ++j)
			{
				mFloor[i][j] = FloorTile::CreateFloor(mFloorBluePrint[i][j], Vector2(j, i), sc);
			}
		}
	}

	void Map::CreateWall(Scene* sc)
	{
		mForeObjects.resize(size.y);
		for (int i = 0; i < size.y; ++i)
		{
			mForeObjects[i].resize(size.x);
			for (int j = 0; j < size.x; ++j)
			{
				mForeObjects[i][j] = WallTile::CreateWall(mWallBluePrint[i][j], Vector2(j, i), sc);
			}
		}
	}

	void Map::OnBeat()
	{
		for (int i = 0; i < size.y; i++)
			for (int j = 0; j < size.x; ++j)
				mFloor[i][j]->OnBeat();
	}

	void Map::DeleteForeGround(Vector2 index)
	{
		object::Destory(mFloor[index.y][index.x]);
		mFloor[index.y][index.x] = nullptr;
	}

	Vector2 Map::GetStartPos()
	{
		return Vector2(startPos.x * GameManager::UnitLength(), startPos.y * GameManager::UnitLength());
	}
#pragma endregion

#pragma region Lobby Map Class
	LobbyMap::LobbyMap()
	{
		size = Vector2(13, 13);
		SetFloor();
		SetWall();
		//startPos = Vector2(6, 3);
	}

	void LobbyMap::SetFloor()
	{
		mFloorBluePrint.resize(size.y);
		for (int i = 0; i < size.y; ++i)
		{
			mFloorBluePrint[i].resize(size.x);
			for (int j = 0; j < size.x; ++j)
			{
				mFloorBluePrint[i][j] = FloorTile::eFloorTypes::Lobby;
			}
		}

		mFloorBluePrint[0][0] = FloorTile::eFloorTypes::None;
		mFloorBluePrint[0][12] = FloorTile::eFloorTypes::None;
		mFloorBluePrint[12][0] = FloorTile::eFloorTypes::None;
		mFloorBluePrint[12][12] = FloorTile::eFloorTypes::None;

		mFloorBluePrint[5][5] = FloorTile::eFloorTypes::OpenedStairs;

		mFloorBluePrint[0][12] = FloorTile::eFloorTypes::None;
		mFloorBluePrint[12][0] = FloorTile::eFloorTypes::None;
		mFloorBluePrint[12][12] = FloorTile::eFloorTypes::None;
	}
	
	void LobbyMap::SetWall()
	{
		mWallBluePrint.resize(size.y);
		for (int i = 0; i < size.y; ++i)
		{
			mWallBluePrint[i].resize(size.x);
			for (int j = 0; j < size.x; ++j)
				mWallBluePrint[i][j] = WallTile::eWallTypes::None;
		}
		for (int j = 1; j < size.x - 1; j++)
		{
			mWallBluePrint[0][j] = WallTile::eWallTypes::GoldWall;
			mWallBluePrint[size.y - 1][j] = WallTile::eWallTypes::GoldWall;
		}
		for (int i = 1; i < size.y - 1; ++i)
		{
			mWallBluePrint[i][0] = WallTile::eWallTypes::GoldWall;
			mWallBluePrint[i][size.x - 1] = WallTile::eWallTypes::GoldWall;
		}
		mWallBluePrint[1][1] = WallTile::eWallTypes::GoldWall;
		mWallBluePrint[1][11] = WallTile::eWallTypes::GoldWall;
		mWallBluePrint[11][1] = WallTile::eWallTypes::GoldWall;
		mWallBluePrint[11][11] = WallTile::eWallTypes::GoldWall;
	}
#pragma endregion
}