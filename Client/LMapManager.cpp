#include "LMapManager.h"
#include "LMap.h"
namespace cl
{
#pragma region MapManager
	float MapManager::_unitLength = 24.0f;
	float MapManager::_unitScale = 3.0f;

	Map* MapManager::mMap;
	void MapManager::CreateMap(MapType type, Scene* sc)
	{
		DestroyMap();
		switch (type)
		{
		default:
		case Lobby:
			mMap = new LobbyMap();
		}
		mMap->CreateMap(sc);
	}
	void MapManager::DestroyMap()
	{
		if (mMap != nullptr)
		{
			delete mMap;
			mMap = nullptr;
		}
	}
	void MapManager::DestroyObject(Vector2 index)
	{
		mMap->DeleteForeGround(index);
	}
#pragma endregion
	
}