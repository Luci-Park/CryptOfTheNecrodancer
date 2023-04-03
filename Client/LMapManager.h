#pragma once
#include "CommonInclude.h"
namespace cl
{
	class FloorTile;
	class WallTile;
	class TileObject;
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

		static bool OnInteractObject(TileObject* object,Vector2 src, Vector2 dest);
		static void OnTileStep(TileObject* object, Vector2 pos);

	private:
		static bool DoesInteractForeground(TileObject* object, Vector2 src, Vector2 dest);
		static bool DoesInteractWall(TileObject* object, Vector2 src, Vector2 dest);
	private:
		static std::vector<std::vector<FloorTile*>> _Floor;
		static std::vector<std::vector<WallTile*>> _Wall;
		static std::vector<std::vector<TileObject*>> _ForeObjects;
		static Vector2 _size;
	};

}

