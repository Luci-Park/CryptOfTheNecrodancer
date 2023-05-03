#include "LDeepBluesMap.h"
namespace cl
{
	DeepBluesMap::DeepBluesMap()
		: mbEntered(false)
		, mbExited(false)
	{
		topY = 5;
		arenaY = topY + 10 - 1;
		bottomY = arenaY + 10 - 1;
	}
	DeepBluesMap::~DeepBluesMap()
	{
	}
	void DeepBluesMap::Update()
	{
		Map::Update();
	}
	void DeepBluesMap::CreateMapBluePrint()
	{
		mMapSize = Vector2(10, 25);
		Map::Initialize(mMapSize);
		SetTop();
		SetArena();
		SetBottom();
		mPlayerIndex = Vector2(4, bottomY - 3);
		mMonsterBluePrint[topY + 1][1] = eMonsterTypes::DeepBlues;
	}
	void DeepBluesMap::SetTop()
	{
		for (int i = 0; i < 6; ++i)
		{
			for (int j = 1; j < 8; ++j)
			{
				if (i == 0 || i == 5 || j == 1 || j == 7)
					mWallBluePrint[i][j] = eWallTypes::BossWall;
				else
					mWallBluePrint[i][j] = eWallTypes::None;
			}
		}
		mWallBluePrint[2][3] = eWallTypes::BossWall;
		mLightPos.push_back(Vector2(3, 2));

		mWallBluePrint[2][5] = eWallTypes::BossWall;
		mLightPos.push_back(Vector2(5, 2));

		mWallBluePrint[4][3] = eWallTypes::BossWall;
		mLightPos.push_back(Vector2(3, 4));

		mWallBluePrint[4][5] = eWallTypes::BossWall;
		mLightPos.push_back(Vector2(5, 4));

		mFloorBluePrint[3][4] = eFloorTypes::OpenedStairs;
		mStairPos.push_back({ Vector2(4, 3), eSceneType::Lobby });
	}
	void DeepBluesMap::SetArena()
	{
		for (int i = topY; i <= arenaY; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				if (i == topY || i == arenaY || j == 0 || j == 9)
					mWallBluePrint[i][j] = eWallTypes::BossWall;
				else
					mWallBluePrint[i][j] = eWallTypes::None;
			}
		}
		mLightPos.push_back(Vector2(3, topY));
		mLightPos.push_back(Vector2(7, topY));
		mLightPos.push_back(Vector2(0, topY + 2));
		mLightPos.push_back(Vector2(0, topY + 6));
		mLightPos.push_back(Vector2(9, topY + 3));
		mLightPos.push_back(Vector2(9, topY + 5));
		mLightPos.push_back(Vector2(2, arenaY));
		mLightPos.push_back(Vector2(6, arenaY));
	}
	void DeepBluesMap::SetBottom()
	{
		for (int i = bottomY; i >= arenaY; i--)
		{
			for (int j = 1; j <= 7; ++j)
			{
				if (i == bottomY || i == arenaY - 1 || j == 1 || j == 7)
					mWallBluePrint[i][j] = eWallTypes::BossWall;
				else
					mWallBluePrint[i][j] = eWallTypes::None;
			}
		}

		for (int i = arenaY; i < arenaY + 4; i++)
		{
			for (int j = 2; j <= 6; ++j)
			{
				if (i == arenaY)
					mWallBluePrint[i][j] = eWallTypes::HorizontalDoor;
				if (j == 2 || j == 6)
					mWallBluePrint[i][j] = eWallTypes::BossWall;
				else if (i != arenaY)
					eWallTypes::None;
			}
		}
		mWallBluePrint[bottomY - 2][3] = eWallTypes::BossWall;
		mWallBluePrint[bottomY - 4][3] = eWallTypes::BossWall;
		mWallBluePrint[bottomY - 2][5] = eWallTypes::BossWall;
		mWallBluePrint[bottomY - 4][5] = eWallTypes::BossWall;
		mLightPos.push_back(Vector2(3, bottomY - 2));
		mLightPos.push_back(Vector2(5, bottomY - 2));
		mLightPos.push_back(Vector2(3, bottomY - 4));
		mLightPos.push_back(Vector2(5, bottomY - 4));
	}
}