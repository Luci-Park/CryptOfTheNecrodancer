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
		int GetIndexFromDirection(Vector2 dir);
		Vector2 GetDirectionFromIndex(int idx);
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

		Room* mParent;
		std::vector<Room*> mChildren;
	};
	struct StartRoom : public Room
	{
		StartRoom(int zone);
		~StartRoom();
	};
	struct RandomRoom : public Room
	{
		RandomRoom(int zone);
		RandomRoom(int zone, int XMaxSize, int YMaxSize);
		virtual ~RandomRoom();

		void SetRoom();
		void CreateCatacombRoom();//0.1
		void CreateDirtRoom();
		void CreateRandomFloors();
		void CreateMonsters();
	};

	struct ExitRoom : RandomRoom
	{
		ExitRoom(int zone);
		ExitRoom(int zone, int XMaxSize, int YMaxSize);
		~ExitRoom();

		void AddBoss();
		void AddStairs();
	};
}

