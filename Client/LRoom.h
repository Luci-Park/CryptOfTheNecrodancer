#pragma once
#include "LuciEngine.h"
namespace cl
{
	struct Room
	{
		Room(int zone);
		virtual ~Room();

		void Reset();
		void SetWall(eWallTypes type);
		void SetColumn(eWallTypes type);
		void SetCorner(eWallTypes type);
		void SetLights(int numbers);
		static eWallTypes GetRandomDirtWall();

		std::vector<std::vector<eFloorTypes>> mFloors;
		std::vector<std::vector<eWallTypes>> mWalls;
		std::vector<std::vector<eMonsterTypes>> mMonsters;
		std::vector<Vector2> mLights;
		std::vector<std::pair<Vector2, eSceneType>> mStairPos;
		Vector2 mSize;
		Vector2 mMiddlePos;
		Vector2 mOffset;
		int mZone;
	};
	struct StartRoom : public Room
	{
		StartRoom(int zone);
		~StartRoom();
	};
	struct RandomRoom : public Room
	{
		RandomRoom(int zone);
		virtual ~RandomRoom();

		void CreateCatacombRoom();//0.1
		void CreateDirtRoom();
		void CreateRandomFloors();
		void CreateMonsters();
	};

	struct ExitRoom : RandomRoom
	{
		ExitRoom(int zone);
		~ExitRoom();

		void AddBoss();
		void AddStairs();
	};
}

