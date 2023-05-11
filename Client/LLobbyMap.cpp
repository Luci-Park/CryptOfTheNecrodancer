#include "LLobbyMap.h"
namespace cl 
{
	LobbyMap::LobbyMap()
	{
	}

	LobbyMap::~LobbyMap()
	{
	}

	void LobbyMap::CreateMapBluePrint()
	{
		mMapSize = Vector2(13, 13);
		Map::Initialize(mMapSize);
		SetFloor();
		SetWall();
		SetLights();
		mPlayerIndex = Vector2(6, 3);
		mMonsterBluePrint[3][3] = eMonsterTypes::YellowSkeleton;
	}

	void LobbyMap::SetFloor()
	{

		mFloorBluePrint[0][0] = eFloorTypes::None;
		mFloorBluePrint[0][12] = eFloorTypes::None;
		mFloorBluePrint[12][0] = eFloorTypes::None;
		mFloorBluePrint[12][12] = eFloorTypes::None;

		mFloorBluePrint[5][5] = eFloorTypes::OpenedStairs;
		mStairPos.resize(1);
		mStairPos[0] = { Vector2(5, 5), eSceneType::Depth1 };
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
		mWallBluePrint[7][3] = eWallTypes::GoldWall;
		mWallBluePrint[5][3] = eWallTypes::GoldWall;
		mWallBluePrint[7][9] = eWallTypes::GoldWall;
		mWallBluePrint[5][9] = eWallTypes::GoldWall;
	}
	void LobbyMap::SetLights()
	{
		mLightPos.push_back(Vector2(1, 0));
		mLightPos.push_back(Vector2(11, 0));
		mLightPos.push_back(Vector2(1, 12));
		mLightPos.push_back(Vector2(11, 12));
		mLightPos.push_back(Vector2(3, 7));
		mLightPos.push_back(Vector2(3, 5));
		mLightPos.push_back(Vector2(9, 7));
		mLightPos.push_back(Vector2(9, 5));
	}
}