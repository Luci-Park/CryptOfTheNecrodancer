#include "LMap.h"
#include "LObject.h"
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

	LobbyMap::LobbyMap()
	{
		size = Vector2(13, 13);
		mFloorBluePrint.resize(13);
		for (int i = 0; i < 13; ++i)
		{
			mFloorBluePrint[i].resize(13);
			for (int j = 0; j < 13; ++j)
			{
				mFloorBluePrint[i][j] = FloorTile::eFloorTypes::Lobby;
			}
		}
		mFloorBluePrint[0][0] = FloorTile::eFloorTypes::None;
		mFloorBluePrint[0][12] = FloorTile::eFloorTypes::None;
		mFloorBluePrint[12][0] = FloorTile::eFloorTypes::None;
		mFloorBluePrint[12][12] = FloorTile::eFloorTypes::None;

		mFloorBluePrint[5][5] = FloorTile::eFloorTypes::Stairs;
		/*
		mFloorBluePrint[0][12] = FloorTile::eFloorTypes::None;
		mFloorBluePrint[12][0] = FloorTile::eFloorTypes::None;
		mFloorBluePrint[12][12] = FloorTile::eFloorTypes::None;*/

	}
}