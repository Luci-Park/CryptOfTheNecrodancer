#pragma once
#include "LuciEngine.h"
#include "LFloorTile.h"
#include "LBeatObject.h"
#include "LWallTile.h"
namespace cl
{
	class TileObject;
	class Map
	{
	public:
		Map();
		~Map();

		std::vector<std::vector<FloorTile*>>& CreateFloor(Scene* sc);
		std::vector<std::vector<TileObject*>>& CreateForeGround(Scene* sc);

		Vector2 GetStartPos();

	protected:
		virtual void SetFloor() = 0;
		virtual void SetWall() = 0;
		Vector2 mMapSize;
		Vector2 mPlayerIndex;
		std::vector<std::vector<FloorTile::eFloorTypes>> mFloorBluePrint;
		std::vector<std::vector<WallTile::eWallTypes>> mWallBluePrint;
		std::vector<std::pair<Vector2, eSceneType>> mStairPos;
		std::vector<std::vector<FloorTile*>> mFloor;
		std::vector<std::vector<TileObject*>> mForeObjects;

	private:
		void CreateWall(Scene* sc);
		void CreatePlayer(Scene* sc);
	};

	class LobbyMap : public Map
	{
	public:
		LobbyMap();
	private:
		virtual void SetFloor();
		virtual void SetWall();
	};

}