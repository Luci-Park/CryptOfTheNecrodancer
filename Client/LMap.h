#pragma once
#include "LuciEngine.h"
#include "LFloorTile.h"
#include "LBeatObject.h"
#include "LWallTile.h"
namespace cl
{
	class TileObject;
	class Map : public BeatObject
	{
	public:
		Map();
		~Map();
		void CreateMap(Scene* sc);
		virtual void OnBeat();
		virtual void OnBeatChanged() {}

		virtual void SetFloor() = 0;
		virtual void SetWall() = 0;

		void DeleteForeGround(Vector2 index);
		Vector2 GetStartPos();
	protected:
		Vector2 mMapSize;
		Vector2 mPlayerStartPos;
		std::vector<std::vector<FloorTile::eFloorTypes>> mFloorBluePrint;
		std::vector<std::vector<WallTile::eWallTypes>> mWallBluePrint;
		std::vector<std::vector<FloorTile*>> mFloor;
		std::vector<std::vector<TileObject*>> mForeObjects;

	private:
		void CreateFloor(Scene* sc);
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