#include "LMapManager.h"
#include "LMap.h"
namespace cl
{
#pragma region MapManager
	std::vector<std::vector<FloorTile*>> MapManager::_Floor = std::vector<std::vector<FloorTile*>>();
	std::vector<std::vector<TileObject*>> MapManager::_ForeObjects = std::vector<std::vector<TileObject*>>();
	float MapManager::_unitLength = 24.0f;
	float MapManager::_unitScale = 3.0f;
	Vector2 MapManager::_size = Vector2::Zero;

	void MapManager::CreateMap(MapType type, Scene* sc)
	{
		DestroyMap();
		Map* mMap;
		switch (type)
		{
		default:
		case Lobby:
			mMap = new LobbyMap();
		}
		_Floor = mMap->CreateFloor(sc);
		_ForeObjects = mMap->CreateForeGround(sc);
		_size.y = _Floor.size();
		_size.x = _Floor[0].size();
		delete mMap;
	}
	void MapManager::DestroyMap()
	{
		std::vector<std::vector<FloorTile*>> mFloor = std::vector<std::vector<FloorTile*>>();
		std::vector<std::vector<TileObject*>> mForeObjects = std::vector<std::vector<TileObject*>>();
		_size = Vector2::Zero;
	}
	void MapManager::DestroyObject(Vector2 index)
	{
		if (_ForeObjects[index.y][index.x] != nullptr)
		{
			_ForeObjects[index.y][index.x]->Destroy();
			_ForeObjects[index.y][index.x] = nullptr;
		}
	}
	void MapManager::Render(HDC hdc)
	{
		for (int i = 0; i < _size.y; ++i)
		{
			for (int j = 0; j < _size.x; ++j)
			{
				if(_ForeObjects[i][j] != nullptr)
					_ForeObjects[i][j]->Render(hdc);
			}
		}
	}
	bool MapManager::OnInteractObject(TileObject* object, Vector2 src, Vector2 dest)
	{
		if (_ForeObjects[dest.y][dest.x] == nullptr)
		{
			_ForeObjects[src.y][src.x] = nullptr;
			_ForeObjects[dest.y][dest.x] = object;
			return false;
		}
		else
		{
			_ForeObjects[dest.y][dest.x]->Interact(object);
			return true;
		}
	}
	void MapManager::OnTileStep(TileObject* object, Vector2 pos)
	{
		if (_Floor[pos.y][pos.x] != nullptr)
		{
			_Floor[pos.y][pos.x]->OnInteract(object);
		}
	}
#pragma endregion
	
}