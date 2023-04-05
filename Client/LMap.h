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

		void CreateFloor(Scene* sc, std::vector<std::vector<FloorTile*>>& _Floor);
		void CreateWall(Scene* sc, std::vector<std::vector<WallTile*>>& _Wall);
		void CreateForeGround(Scene* sc, std::vector<std::vector<TileObject*>>& _TileObjects);
		Vector2 GetPlayerPos() { return mPlayerIndex; }

	protected:
		virtual void SetFloor() = 0;
		virtual void SetWall() = 0;
		Vector2 mMapSize;
		Vector2 mPlayerIndex;
		std::vector<std::vector<eFloorTypes>> mFloorBluePrint;
		std::vector<std::vector<eWallTypes>> mWallBluePrint;
		std::vector<std::pair<Vector2, eSceneType>> mStairPos;

	private:
		void CreatePlayer(Scene* sc, std::vector<std::vector<TileObject*>>& _TileObjects);
		void CreateMonsters(Scene* sc, std::vector<std::vector<TileObject*>>& _TileObjects);
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