#include "LMap.h"
#include "LObject.h"
#include "LGameManager.h"
namespace cl
{
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
	void Map::OnBeat()
	{
		for (int i = 0; i < size.y; i++)
			for (int j = 0; j < size.x; ++j)
				mFloor[i][j]->OnBeat();
	}

	Vector2 Map::GetStartPos()
	{
		return Vector2(startPos.x * GameManager::UnitLength(), startPos.y * GameManager::UnitLength());
	}

	LobbyMap::LobbyMap()
	{
		size = Vector2(13, 13);
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

		startPos = Vector2(6, 3);
	}
}