#pragma once
#include "LuciEngine.h"
#include "LFloorTile.h"
#include "LBeatObject.h"
#include "LWallTile.h"
#include "LItem.h"
#include "LTileLight.h"
namespace cl
{
	class FloorTile;
	class WallTile;
	class TileObject;
	class Item;
	class Cadence;
	class LightSource;
	class Map
	{
	public:
		Map();
		~Map();

		void DestroyTileObject(Vector2 index);
		void DestroyWallObject(Vector2 index);

		virtual void Update();
		void Render(HDC hdc);
		
		void AddLightSource(LightSource* light);
		void RemoveLightSource(LightSource* light);

		void SetLight(Vector2 pos, float brightness);
		TileLight* GetLight(Vector2 pos);
		void OnTileStep(TileObject* object, Vector2 pos);

		WallTile* GetWall(Vector2 index);
		TileObject* GetTileObject(Vector2 index);
		Cadence* GetPlayer(Vector2 index);
		Vector2 GetPlayerIndex() { return mPlayerIndex; }
		Item* GetItem(Vector2 index);
		Vector2 SetItem(Item* item, Vector2 pos);

		void PlayerMove(TileObject* object, Vector2 src, Vector2 dest);
		void Move(TileObject* object, Vector2 src, Vector2 dest);
		
		
		void CreateMap(Scene* sc);
		Vector2 GetPlayerPos() { return mPlayerIndex; }

		static Vector2 GetTilePosOfIndex(Vector2 pos) { return pos * UNITLENGTH; }
	protected:
		virtual void SetFloor() = 0;
		virtual void SetWall() = 0;
		bool IndexIsValid(Vector2 index);
		Vector2 mMapSize;
		Vector2 mPlayerIndex;

		std::vector<std::vector<eFloorTypes>> mFloorBluePrint;
		std::vector<std::vector<eWallTypes>> mWallBluePrint;
		std::vector<std::pair<Vector2, eSceneType>> mStairPos;
		
	private:
		void CalculateLight();

		void CreateFloor(Scene* sc);
		void CreateWall(Scene* sc);
		void CreateForeGround(Scene* sc);
		void CreateItems(Scene* sc);
		void CreatePlayer(Scene* sc);
		void CreateMonsters(Scene* sc);
		void CreateLight(Scene* sc);
		void CreateLightInfo();
		std::vector<std::vector<FloorTile*>> mFloor;
		std::vector<std::vector<WallTile*>> mWall;
		std::vector<std::vector<Item*>> mItems;
		std::vector<std::vector<TileObject*>> mTileObjects;
		std::vector<std::vector<TileLight*>> mLightStatus;
		std::vector<LightSource*>mLightSources;
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