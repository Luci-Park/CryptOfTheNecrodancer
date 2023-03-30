#pragma once
#include "CommonInclude.h"
namespace cl
{
	class FloorTile;
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
		static void DestroyObject(Vector2 index);
		 
		static void Render(HDC hdc);

		static bool OnInteractObject(TileObject* object,Vector2 src, Vector2 destination);

		static float UnitLength() { return _unitLength * _unitScale; }
		static float UnitScale() { return _unitScale; }

	private:

		static std::vector<std::vector<FloorTile*>> _Floor;
		static std::vector<std::vector<TileObject*>> _ForeObjects;
		static Vector2 _size;
		static float _unitScale;
		static float _unitLength;
	};

}

