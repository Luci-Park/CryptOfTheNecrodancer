#include "LMap.h"
#include "LBeatManager.h"
#include "LObject.h"
#include "LCadence.h"
#include "LBlueSlime.h"
#include "LGreenSlime.h"
#include "LOrangeSlime.h"
namespace cl
{
#pragma region Parent - Map Class
	Map::Map()
	{
	}

	Map::~Map()
	{
	}

	void Map::CreateFloor(Scene* sc, std::vector<std::vector<FloorTile*>>& _Floor)
	{
		_Floor.resize(mMapSize.y);
		for (int i = 0; i < mMapSize.y; ++i)
		{
			_Floor[i].resize(mMapSize.x);
			for (int j = 0; j < mMapSize.x; ++j)
			{
				_Floor[i][j] = FloorTile::CreateFloor(mFloorBluePrint[i][j], Vector2(j, i), sc);
				if (_Floor[i][j] != nullptr)
					BeatManager::AddCharacters(_Floor[i][j]);
			}
		}
		for (int i = 0; i < mStairPos.size(); ++i)
		{
			Vector2 pos = mStairPos[i].first;
			StairTile* tile = dynamic_cast<StairTile*>(_Floor[pos.y][pos.x]);
			tile->SetDestination(mStairPos[i].second);
		}
	}

	void Map::CreateWall(Scene* sc, std::vector<std::vector<WallTile*>>& _Wall)
	{
		_Wall.resize(mMapSize.y);
		for (int i = 0; i < mMapSize.y; ++i)
		{
			_Wall[i].resize(mMapSize.x);
			for (int j = 0; j < mMapSize.x; ++j)
			{
				_Wall[i][j] = WallTile::CreateWall(mWallBluePrint[i][j], Vector2(j, i), sc);
			}
		}
	}

	void Map::CreateForeGround(Scene* sc, std::vector<std::vector<TileObject*>>& _TileObjects)
	{
		CreateMonsters(sc, _TileObjects);
		CreatePlayer(sc, _TileObjects);
	}

	void Map::CreatePlayer(Scene* sc, std::vector<std::vector<TileObject*>>& _TileObjects)
	{
		Vector2 pos;
		pos.x = (mPlayerIndex.x ) * UNITLENGTH;
		pos.y = (mPlayerIndex.y - 0.25) * UNITLENGTH;
		Cadence* cadence = object::Instantiate<Cadence>(sc, pos, eLayerType::Player);
		_TileObjects[mPlayerIndex.y][mPlayerIndex.x] = cadence;
		cadence->SetIndex(mPlayerIndex);
		BeatManager::AddCharacters(cadence);
	}

	void Map::CreateMonsters(Scene* sc, std::vector<std::vector<TileObject*>>& _TileObjects)
	{
		_TileObjects.resize(mMapSize.y);
		for (int i = 0; i < mMapSize.y; ++i)
		{
			_TileObjects[i].resize(mMapSize.x);
			for (int j = 0; j < mMapSize.x; ++j)
			{
				_TileObjects[i][j] = nullptr;
				if (j == 4 && i == 4)
				{
					Vector2 pos;
					pos.x = j * UNITLENGTH;
					pos.y = (i - 0.25) * UNITLENGTH;
					_TileObjects[i][j] = object::Instantiate<OrangeSlime>(sc, pos, eLayerType::Monster);
					_TileObjects[i][j]->SetIndex(Vector2(j, i));
				}
				if (j == 6 && i == 8)
				{
					Vector2 pos;
					pos.x = j * UNITLENGTH;
					pos.y = (i - 0.25) * UNITLENGTH;
					_TileObjects[i][j] = object::Instantiate<GreenSlime>(sc, pos, eLayerType::Monster);
					_TileObjects[i][j]->SetIndex(Vector2(j, i));
				}
				if (j == 1 && i == 2)
				{
					Vector2 pos;
					pos.x = j * UNITLENGTH;
					pos.y = (i - 0.25) * UNITLENGTH;
					_TileObjects[i][j] = object::Instantiate<BlueSlime>(sc, pos, eLayerType::Monster);
					_TileObjects[i][j]->SetIndex(Vector2(j, i));
				}
			}
		}
	}
#pragma endregion

#pragma region Lobby Map Class
	LobbyMap::LobbyMap()
	{
		mMapSize = Vector2(13, 13);
		SetFloor();
		SetWall();
		mPlayerIndex = Vector2(6, 3);
	}

	void LobbyMap::SetFloor()
	{
		mFloorBluePrint.resize(mMapSize.y);
		for (int i = 0; i < mMapSize.y; ++i)
		{
			mFloorBluePrint[i].resize(mMapSize.x);
			for (int j = 0; j < mMapSize.x; ++j)
			{
				mFloorBluePrint[i][j] = eFloorTypes::Ground;
			}
		}

		mFloorBluePrint[0][0] = eFloorTypes::None;
		mFloorBluePrint[0][12] = eFloorTypes::None;
		mFloorBluePrint[12][0] = eFloorTypes::None;
		mFloorBluePrint[12][12] = eFloorTypes::None;

		mFloorBluePrint[5][5] = eFloorTypes::OpenedStairs;

		mFloorBluePrint[3][5] = eFloorTypes::Water;
		mFloorBluePrint[3][4] = eFloorTypes::Water;
		mFloorBluePrint[3][3] = eFloorTypes::Water;

		mStairPos.resize(1);
		mStairPos[0] = { Vector2(5, 5), eSceneType::Splash };
	}
	
	void LobbyMap::SetWall()
	{
		mWallBluePrint.resize(mMapSize.y);
		for (int i = 0; i < mMapSize.y; ++i)
		{
			mWallBluePrint[i].resize(mMapSize.x);
			for (int j = 0; j < mMapSize.x; ++j)
				mWallBluePrint[i][j] = eWallTypes::None;
		}
		for (int j = 1; j < mMapSize.x - 1; j++)
		{
			mWallBluePrint[0][j] = eWallTypes::GoldWall;
			mWallBluePrint[mMapSize.y - 1][j] = eWallTypes::GoldWall;
		}
		for (int i = 1; i < mMapSize.y - 1; ++i)
		{
			mWallBluePrint[i][0] = eWallTypes::GoldWall;
			mWallBluePrint[i][mMapSize.x - 1] = eWallTypes::GoldWall;
		}
		mWallBluePrint[1][1] = eWallTypes::GoldWall;
		mWallBluePrint[1][11] = eWallTypes::GoldWall;
		mWallBluePrint[11][1] = eWallTypes::GoldWall;
		mWallBluePrint[11][11] = eWallTypes::GoldWall;

		mWallBluePrint[2][2] = eWallTypes::DirtWall;
		mWallBluePrint[3][2] = eWallTypes::StoneWall;
		mWallBluePrint[4][2] = eWallTypes::CatacombWall;
		mWallBluePrint[5][2] = eWallTypes::BossWall;/*
		mWallBluePrint[6][2] = eWallTypes::HorizontalDoor;
		mWallBluePrint[7][2] = eWallTypes::VerticalDoor;*/

	}
#pragma endregion
}