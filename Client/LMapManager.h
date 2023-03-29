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
	private:
		static Map* mMap;
		
	};

}

