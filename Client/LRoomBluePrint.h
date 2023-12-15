#pragma once
#include "LuciEngine.h"
namespace cl
{
	struct RoomBluePrint
	{
		RoomBluePrint(int zone);
		virtual ~RoomBluePrint();

		void Reset();
		void SetWall(eWallTypes type);
		void SetColumn(eWallTypes type);
		void SetCorner(eWallTypes type);
		void SetLights(int numbers);
		static int GetIndexFromDirection(Vector2 dir);
		static Vector2 GetDirectionFromIndex(int idx);
		static eWallTypes GetRandomDirtWall();

		std::vector<std::vector<eFloorTypes>> mFloors;
		std::vector<std::vector<eWallTypes>> mWalls;
		std::vector<std::vector<eMonsterTypes>> mMonsters;
		std::vector<Vector2> mLights;
		std::vector<std::pair<Vector2, eSceneType>> mStairPos;
		Vector2 mSize;
		Vector2 mCenter;
		Vector2 mOffset;
		int mZone;

		RoomBluePrint* mParent;
		std::vector<RoomBluePrint*> mChildren;
	};
	struct StartRoom : public RoomBluePrint
	{
		StartRoom(int zone);
		~StartRoom();
	};
	struct RandomRoom : public RoomBluePrint
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

