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
	private:
		static Map* mMap;
		
	};

}

