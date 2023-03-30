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
		void CreateMap(Scene* sc);

		virtual void SetFloor() = 0;
		virtual void SetWall() = 0;

		void DeleteForeGround(Vector2 index);
		Vector2 GetStartPos();
		//Return true if interaction happened
		bool OnInteractObject(TileObject* object, Vector2 src, Vector2 dest);

	protected:
		Vector2 mMapSize;
		Vector2 mPlayerIndex;
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