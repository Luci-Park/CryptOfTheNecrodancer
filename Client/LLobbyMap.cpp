#include "LLobbyMap.h"
namespace cl 
{
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
}