#pragma once
#include "CommonInclude.h"
namespace cl
{
	class FloorTile;
	class WallTile;
	class TileObject;
	class LightSource;
	class TileLight;
	class Item;
	class Cadence;
	class Map;
	class Scene;
	class MapManager
	{
	public:
		enum MapType
		{
			Lobby,
			Tutorial,
			Random1,
			Random2,
			Random3,
			DeepBlues
		};
		static void CreateMap(MapType type, Scene* sc);
		static void DestroyMap();
		static void DestroyTileObject(Vector2 index);
		static void DestroyWallObject(Vector2 index);
		 
		static void Update();
		static void Render(HDC hdc);

		static void AddLightSource(LightSource* light);
		static void RemoveLightSource(LightSource* light);

		static void SetLight(Vector2 index, float brightness);
		static TileLight* GetLight(Vector2 index);

		static void OnTileStep(TileObject* object, Vector2 pos);

		static WallTile* GetWall(Vector2 index);
		static TileObject* GetEnemy(Vector2 index);
		static TileObject* GetTileObject(Vector2 index);
		static Cadence* GetPlayer(Vector2 index);
		static Vector2 GetPlayerIndex();
		static Item* GetItem(Vector2 index);
		static Vector2 SetItem(Item* item, Vector2 pos);
		static void PlayerMove(TileObject* object, Vector2 src, Vector2 dest);
		static void Move(TileObject* object, Vector2 src, Vector2 dest);
		static bool IndexIsValid(Vector2 index);
	private:
		static Map* _Map;
	};

}

