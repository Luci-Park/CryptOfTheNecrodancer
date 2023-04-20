#include "LMap.h"
#include "LBeatManager.h"
#include "LObject.h"
#include "LCadence.h"
#include "LShovel.h"
#include "LZombie.h"
#include "LSkeleton.h"
#include "LRedBat.h"
#include "LOrangeSlime.h"
#include "LBlueSlime.h"
#include "LWallTorch.h"
namespace cl
{
#pragma region Parent - Map Class
	Map::Map()
	{
	}

	Map::~Map()
	{
		for (int i = 0; i < mMapSize.y; ++i)
		{
			for (int j = 0; j < mMapSize.x; ++j)
			{
				delete mLightStatus[i][j];
				mLightStatus[i][j] = nullptr;
			}

		}
	}

#pragma region MapInteraction
	void Map::DestroyTileObject(Vector2 index)
	{
		if (mTileObjects[index.y][index.x] != nullptr)
		{
			mTileObjects[index.y][index.x]->Destroy();
			mTileObjects[index.y][index.x] = nullptr;
		}
	}
	void Map::DestroyWallObject(Vector2 index)
	{
		if (mWall[index.y][index.x] != nullptr)
		{
			mWall[index.y][index.x]->Destroy();
			mWall[index.y][index.x] = nullptr;
		}
	}
	void Map::Update()
	{
		CalculateLight();
	}
	void Map::Render(HDC hdc)
	{
		for (int i = 0; i < mMapSize.y; ++i)
		{
			for (int j = 0; j < mMapSize.x; ++j)
			{
				if (mWall[i][j] != nullptr)
					mWall[i][j]->Render(hdc);
				if (mTileObjects[i][j] != nullptr)
					mTileObjects[i][j]->Render(hdc);
			}
		}
	}
	void Map::CalculateLight()
	{
		for (int i = 0; i < mMapSize.y; ++i)
		{
			for (int j = 0; j < mMapSize.x; ++j)
			{
				mLightStatus[i][j]->Reset();
			}
		}
		for (int i = 0; i < mMapSize.y; ++i)
		{
			for (int j = 0; j < mMapSize.x; ++j)
			{
				if(mTileObjects[i][j] != nullptr)
					mTileObjects[i][j]->CalLightBrightness();
			}
		}
		for (int i = 0; i < mMapSize.y; ++i)
		{
			for (int j = 0; j < mMapSize.x; ++j)
			{
				mLightStatus[i][j]->CheckIfInSight(mPlayerIndex);
			}
		}
	}
	void Map::SetLight(Vector2 pos, float brightness)
	{
		if (IndexIsValid(pos))
		{
			mLightStatus[pos.y][pos.x]->AddIllumination(brightness);
		}
	}
	TileLight* Map::GetLight(Vector2 pos)
	{
		if (IndexIsValid(pos))
		{
			return mLightStatus[pos.y][pos.x];
		}
		return nullptr;
	}
	void Map::OnTileStep(TileObject* object, Vector2 pos)
	{
		if (mFloor[pos.y][pos.x] != nullptr)
		{
			mFloor[pos.y][pos.x]->OnInteract(object);
		}
	}
	WallTile* Map::GetWall(Vector2 index)
	{
		return mWall[index.y][index.x];
	}
	TileObject* Map::GetTileObject(Vector2 index)
	{
		if (index == mPlayerIndex) return nullptr;
		return mTileObjects[index.y][index.x];
	}
	Cadence* Map::GetPlayer(Vector2 index)
	{
		if (index == mPlayerIndex)
			return (Cadence*)mTileObjects[index.y][index.x];
		return nullptr;
	}
	Item* Map::GetItem(Vector2 index)
	{
		return mItems[index.y][index.x];
	}
	Vector2 Map::SetItem(Item* item, Vector2 pos)
	{
		mItems[pos.y][pos.x] = item;
		return pos * UNITLENGTH;
	}
	void Map::PlayerMove(TileObject* object, Vector2 src, Vector2 dest)
	{
		Move(object, src, dest);
		mPlayerIndex = dest;
	}
	void Map::Move(TileObject* object, Vector2 src, Vector2 dest)
	{
		if (src == dest) return;
		mTileObjects[dest.y][dest.x] = object;
		if (mTileObjects[src.y][src.x] == object) mTileObjects[src.y][src.x] = nullptr;
	}
#pragma endregion
#pragma region Map Creation


	void Map::CreateMap(Scene* sc)
	{
		CreateFloor(sc);
		CreateWall(sc);
		CreateForeGround(sc);
		CreateItems(sc);
		CreateLight(sc);
		CreateLightInfo();
	}

	bool Map::IndexIsValid(Vector2 index)
	{
		if (0 <= index.x && index.x < mMapSize.x
			&& 0 <= index.y && index.y < mMapSize.y)
			return true;
		return false;
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
				if (mFloor[i][j] != nullptr)
					BeatManager::AddCharacters(mFloor[i][j]);
			}
		}
		for (int i = 0; i < mStairPos.size(); ++i)
		{
			Vector2 pos = mStairPos[i].first;
			StairTile* tile = dynamic_cast<StairTile*>(mFloor[pos.y][pos.x]);
			tile->SetDestination(mStairPos[i].second);
		}
	}

	void Map::CreateWall(Scene* sc)
	{
		mWall.resize(mMapSize.y);
		for (int i = 0; i < mMapSize.y; ++i)
		{
			mWall[i].resize(mMapSize.x);
			for (int j = 0; j < mMapSize.x; ++j)
			{
				mWall[i][j] = WallTile::CreateWall(mWallBluePrint[i][j], Vector2(j, i), sc);
			}
		}
	}

	void Map::CreateForeGround(Scene* sc)
	{
		CreateMonsters(sc);
		CreatePlayer(sc);
	}

	void Map::CreateItems(Scene* sc)
	{
		mItems.resize(mMapSize.y);
		for (int i = 0; i < mMapSize.y; ++i)
		{
			mItems[i].resize(mMapSize.x);
			if (i == 3)
			{
				PickAxe* object = object::Instantiate<PickAxe>(sc, eLayerType::Items);
				mItems[i][10] = object;
				object->SetItem(Vector2(10, 3) * UNITLENGTH);
			}
		}
	}

	void Map::CreatePlayer(Scene* sc)
	{
		Cadence* cadence = object::Instantiate<Cadence>(sc, mPlayerIndex*UNITLENGTH, eLayerType::Player);
		mTileObjects[mPlayerIndex.y][mPlayerIndex.x] = cadence;
		cadence->SetIndex(mPlayerIndex);
		BeatManager::AddCharacters(cadence);
	}

	void Map::CreateMonsters(Scene* sc)
	{
		mTileObjects.resize(mMapSize.y);
		for (int i = 0; i < mMapSize.y; ++i)
		{
			mTileObjects[i].resize(mMapSize.x);
			for (int j = 0; j < mMapSize.x; ++j)
			{
				mTileObjects[i][j] = nullptr;
				if (i == 8)
				{
					if(j > 3 && j< 7)
					{
						Vector2 pos;
						pos.x = j * UNITLENGTH;
						pos.y = i * UNITLENGTH;
						mTileObjects[i][j] = object::Instantiate<BlueSlime>(sc, pos, eLayerType::Monster);
						mTileObjects[i][j]->SetIndex(Vector2(j, i));
					}
				}
			}
		}
	}
	void Map::CreateLight(Scene* sc)
	{
		Vector2 pos = Vector2(1, 0);
		mTileObjects[pos.y][pos.x] = object::Instantiate<WallTorch>(sc, pos * UNITLENGTH, eLayerType::Monster);
		mTileObjects[pos.y][pos.x]->SetIndex(pos);
		pos = Vector2(11, 0);
		mTileObjects[pos.y][pos.x] = object::Instantiate<WallTorch>(sc, pos * UNITLENGTH, eLayerType::Monster);
		mTileObjects[pos.y][pos.x]->SetIndex(pos);
		pos = Vector2(1, 12);
		mTileObjects[pos.y][pos.x] = object::Instantiate<WallTorch>(sc, pos * UNITLENGTH, eLayerType::Monster);
		mTileObjects[pos.y][pos.x]->SetIndex(pos);
		pos = Vector2(11, 12);
		mTileObjects[pos.y][pos.x] = object::Instantiate<WallTorch>(sc, pos * UNITLENGTH, eLayerType::Monster);
		mTileObjects[pos.y][pos.x]->SetIndex(pos);
	}
	void Map::CreateLightInfo()
	{
		mLightStatus.resize(mMapSize.y);
		for (int i = 0; i < mMapSize.y; ++i)
		{
			mLightStatus[i].resize(mMapSize.x);
			for (int j = 0; j < mMapSize.x; ++j)
			{
				mLightStatus[i][j] = new TileLight(Vector2(j, i));
			}
		}
		CalculateLight();
	}
#pragma endregion
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
				mFloorBluePrint[i][j] = eFloorTypes::ActiveDirt;
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
		mWallBluePrint[5][2] = eWallTypes::BossWall;
		mWallBluePrint[6][2] = eWallTypes::VerticalDoor;
		mWallBluePrint[7][2] = eWallTypes::HorizontalDoor;


	}
#pragma endregion
}