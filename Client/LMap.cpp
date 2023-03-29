#include "LMap.h"
#include "LObject.h"
#include "LGameManager.h"
#include "LCadence.h"
namespace cl
{
#pragma region Parent - Map Class
	Map::Map()
	{
	}

	Map::~Map()
	{
		for (int i = 0; i < mMapSize.y; ++i)
			for (int j = 0; j < mMapSize.x; ++j)
			{
				object::Destory(mFloor[i][j]);
				object::Destory(mForeObjects[i][j]);
				mFloor[i][j] = nullptr;
				mForeObjects[i][j] = nullptr;
			}
	}
	
	void Map::CreateMap(Scene* sc)
	{
		CreateFloor(sc);
		CreateWall(sc);
		CreatePlayer(sc);
	}

	void Map::CreateFloor(Scene* sc)
	{
		mFloor.resize(mMapSize.y);
		for (int i = 0; i < mMapSize.y; ++i)
		{
			mFloor[i].resize(mMapSize.x);
			for (int j = 0; j < mMapSize.x; ++j)
			{
				mFloor[i][j] = FloorTile::CreateFloor(mFloorBluePrint[i][j], Vector2(j, i), sc);
			}
		}
	}

	void Map::CreateWall(Scene* sc)
	{
		mForeObjects.resize(mMapSize.y);
		for (int i = 0; i < mMapSize.y; ++i)
		{
			mForeObjects[i].resize(mMapSize.x);
			for (int j = 0; j < mMapSize.x; ++j)
			{
				mForeObjects[i][j] = WallTile::CreateWall(mWallBluePrint[i][j], Vector2(j, i), sc);
			}
		}
	}

	void Map::CreatePlayer(Scene* sc)
	{
		mPlayerStartPos.x = (mPlayerStartPos.x + 0.5) * GameManager::UnitLength();
		mPlayerStartPos.y = (mPlayerStartPos.y + 0.5) * GameManager::UnitLength();
		object::Instantiate<Cadence>(sc, mPlayerStartPos, eLayerType::Player);
	}

	void Map::OnBeat()
	{
		for (int i = 0; i < mMapSize.y; i++)
			for (int j = 0; j < mMapSize.x; ++j)
				mFloor[i][j]->OnBeat();
	}

	void Map::DeleteForeGround(Vector2 index)
	{
		object::Destory(mFloor[index.y][index.x]);
		mFloor[index.y][index.x] = nullptr;
	}

	Vector2 Map::GetStartPos()
	{
		return Vector2(mPlayerStartPos.x * GameManager::UnitLength(), mPlayerStartPos.y * GameManager::UnitLength());
	}
#pragma endregion

#pragma region Lobby Map Class
	LobbyMap::LobbyMap()
	{
		mMapSize = Vector2(13, 13);
		SetFloor();
		SetWall();
		mPlayerStartPos = Vector2(6, 3);
	}

	void LobbyMap::SetFloor()
	{
		mFloorBluePrint.resize(mMapSize.y);
		for (int i = 0; i < mMapSize.y; ++i)
		{
			mFloorBluePrint[i].resize(mMapSize.x);
			for (int j = 0; j < mMapSize.x; ++j)
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
		mWallBluePrint.resize(mMapSize.y);
		for (int i = 0; i < mMapSize.y; ++i)
		{
			mWallBluePrint[i].resize(mMapSize.x);
			for (int j = 0; j < mMapSize.x; ++j)
				mWallBluePrint[i][j] = WallTile::eWallTypes::None;
		}
		for (int j = 1; j < mMapSize.x - 1; j++)
		{
			mWallBluePrint[0][j] = WallTile::eWallTypes::GoldWall;
			mWallBluePrint[mMapSize.y - 1][j] = WallTile::eWallTypes::GoldWall;
		}
		for (int i = 1; i < mMapSize.y - 1; ++i)
		{
			mWallBluePrint[i][0] = WallTile::eWallTypes::GoldWall;
			mWallBluePrint[i][mMapSize.x - 1] = WallTile::eWallTypes::GoldWall;
		}
		mWallBluePrint[1][1] = WallTile::eWallTypes::GoldWall;
		mWallBluePrint[1][11] = WallTile::eWallTypes::GoldWall;
		mWallBluePrint[11][1] = WallTile::eWallTypes::GoldWall;
		mWallBluePrint[11][11] = WallTile::eWallTypes::GoldWall;
	}
#pragma endregion
}