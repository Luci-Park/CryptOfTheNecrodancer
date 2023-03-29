#pragma once
namespace cl
{
	class Map;
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

		static float UnitLength() { return _unitLength * _unitScale; }
		static float UnitScale() { return _unitScale; }

	private:
		static Map* mMap;
		static float _unitScale;
		static float _unitLength;		
	};

}

