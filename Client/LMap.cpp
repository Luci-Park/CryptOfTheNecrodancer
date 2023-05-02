#include "LMap.h"
#include "LBeatManager.h"
#include "LObject.h"
#include "LLightSource.h"
#include "LCadence.h"
#include "LMonsterFactory.h"
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
				{
					TileObject* t = mTileObjects[i][j];
					mTileObjects[i][j]->Render(hdc);
				}
			}
		}
	}
	void Map::AddLightSource(LightSource* light)
	{
		if(light != nullptr)
			mLightSources.push_back(light);
	}
	void Map::RemoveLightSource(LightSource* light)
	{
		auto it = std::find(mLightSources.begin(), mLightSources.end(), light);
		if (it != mLightSources.end())
			mLightSources.erase(it);
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
		for (int i = 0; i < mLightSources.size(); ++i)
		{
			if(mLightSources[i] != nullptr && mLightSources[i]->IsActive())
				mLightSources[i]->CalLightBrightness();
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
		if (!IndexIsValid(index)) return nullptr;
		return mWall[index.y][index.x];
	}
	TileObject* Map::GetEnemy(Vector2 index)
	{
		if (!IndexIsValid(index)) return nullptr;
		if (index == mPlayerIndex) return nullptr;
		return mTileObjects[index.y][index.x];
	}
	TileObject* Map::GetTileObject(Vector2 index)
	{
		if (!IndexIsValid(index)) return nullptr;
		return mTileObjects[index.y][index.x];
	}
	Cadence* Map::GetPlayer(Vector2 index)
	{
		if (!IndexIsValid(index)) return nullptr;
		if (index == mPlayerIndex)
			return (Cadence*)mTileObjects[index.y][index.x];
		return nullptr;
	}
	Item* Map::GetItem(Vector2 index)
	{
		if (!IndexIsValid(index)) return nullptr;
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
		CreateMapBluePrint();
		CreateFloor(sc);
		CreateWall(sc);
		CreateForeGround(sc);
		CreateItems(sc);
		CreateLight(sc);
		CreateLightInfo();
	}

	void Map::Initialize(Vector2 size)
	{
		mFloorBluePrint = std::vector<std::vector<eFloorTypes>>(size.y, std::vector<eFloorTypes>(size.x, eFloorTypes::ActiveDirt));
		mWallBluePrint = std::vector<std::vector<eWallTypes>>(size.y, std::vector<eWallTypes>(size.x, eWallTypes::Border));
		mMonsterBluePrint = std::vector<std::vector<eMonsterTypes>>(size.y, std::vector<eMonsterTypes>(size.x, eMonsterTypes::None));
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
			if(tile != nullptr) tile->SetDestination(mStairPos[i].second);
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
				mTileObjects[i][j] = MonsterFactory::CreateMonster(mMonsterBluePrint[i][j], Vector2(j, i), sc);
				if (mMonsterBluePrint[i][j] != eMonsterTypes::None)
				{
					TileObject* t = mTileObjects[i][j];
				}
			}
		}
	}
	void Map::CreateLight(Scene* sc)
	{
		for (int i = 0; i < mLightPos.size(); ++i)
		{
			if (IndexIsValid(mLightPos[i]))
			{
				mTileObjects[mLightPos[i].y][mLightPos[i].x] = object::Instantiate<WallTorch>(sc, mLightPos[i] * UNITLENGTH, eLayerType::Monster);
				mTileObjects[mLightPos[i].y][mLightPos[i].x]->SetIndex(mLightPos[i]);
			}
		}
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
}