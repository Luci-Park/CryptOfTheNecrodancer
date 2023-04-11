#pragma once
#include "CommonInclude.h"
namespace cl
{
	class FloorTile;
	class WallTile;
	class TileObject;
	class Item;
	class Cadence;
	class MapManager
	{
	public:
		enum MapType
		{
			Lobby,
			Tutorial,
			Random
		};
		static void CreateMap(MapType type, Scene* sc);
		static void DestroyMap();
		static void DestroyTileObject(Vector2 index);
		static void DestroyWallObject(Vector2 index);
		 
		static void Render(HDC hdc);

		static void OnTileStep(TileObject* object, Vector2 pos);

		static WallTile* GetWall(Vector2 index);
		static TileObject* GetMonster(Vector2 index);
		static Cadence* GetPlayer(Vector2 index);
		static Vector2 GetPlayerIndex() { return _playerIndex; }
		static Item* GetItem(Vector2 index);
		static Vector2 SetItem(Item* item, Vector2 pos);
		static void PlayerMove(Vector2 src, Vector2 dest);
		static void Move(Vector2 src, Vector2 dest);

	private:
		static std::vector<std::vector<FloorTile*>> _Floor;
		static std::vector<std::vector<WallTile*>> _Wall;
		static std::vector<std::vector<Item*>> _Items;
		static std::vector<std::vector<TileObject*>> _ForeObjects;
		static Vector2 _size;
		static Vector2 _playerIndex;
	};

}

