#include "LMapManager.h"
#include "LMap.h"
namespace cl
{
#pragma region MapManager
	std::vector<std::vector<FloorTile*>> MapManager::_Floor = std::vector<std::vector<FloorTile*>>();
	std::vector<std::vector<WallTile*>> MapManager::_Wall = std::vector<std::vector<WallTile*>>();
	std::vector<std::vector<TileObject*>> MapManager::_ForeObjects = std::vector<std::vector<TileObject*>>();
	std::vector<std::vector<Item*>> MapManager::_Items = std::vector<std::vector<Item*>>();
	Vector2 MapManager::_size = Vector2::Zero;
	Vector2 MapManager::_playerIndex = Vector2::Zero;

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
		mMap->CreateFloor(sc, _Floor);
		mMap->CreateWall(sc, _Wall);
		mMap->CreateForeGround(sc, _ForeObjects);
		mMap->CreateItems(sc, _Items);
		
		_playerIndex = mMap->GetPlayerPos();
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
	void MapManager::DestroyTileObject(Vector2 index)
	{
		if (_ForeObjects[index.y][index.x] != nullptr)
		{
			_ForeObjects[index.y][index.x]->Destroy();
			_ForeObjects[index.y][index.x] = nullptr;
		}
	}
	void MapManager::DestroyWallObject(Vector2 index)
	{
		if (_Wall[index.y][index.x] != nullptr)
		{
			_Wall[index.y][index.x]->Destroy();
			_Wall[index.y][index.x] = nullptr;
		}
	}
	void MapManager::Render(HDC hdc)
	{
		for (int i = 0; i < _size.y; ++i)
		{
			for (int j = 0; j < _size.x; ++j)
			{
				if (_Wall[i][j] != nullptr)
					_Wall[i][j]->Render(hdc);
				if(_ForeObjects[i][j] != nullptr)
					_ForeObjects[i][j]->Render(hdc);
			}
		}
	}
	void MapManager::OnTileStep(TileObject* object, Vector2 pos)
	{
		if (_Floor[pos.y][pos.x] != nullptr)
		{
			_Floor[pos.y][pos.x]->OnInteract(object);
		}
	}
	WallTile* MapManager::GetWall(Vector2 index)
	{
		return _Wall[index.y][index.x];
	}
	TileObject* MapManager::GetObject(Vector2 index)
	{
		if (index == _playerIndex) return nullptr;
		return _ForeObjects[index.y][index.x];
	}
	Cadence* MapManager::GetPlayer(Vector2 index)
	{
		if (index == _playerIndex)
			return (Cadence*)_ForeObjects[index.y][index.x];
		return nullptr;
	}
	Item* MapManager::GetItem(Vector2 index)
	{
		return _Items[index.y][index.x];
	}
	Vector2 MapManager::SetItem(Item* item, Vector2 pos)
	{
		_Items[pos.y][pos.x] = item;
		return pos * UNITLENGTH;
	}
	void MapManager::PlayerMove(TileObject* object, Vector2 src, Vector2 dest)
	{
		Move(object, src, dest);
		_playerIndex = dest;
	}
	void MapManager::Move(TileObject* object, Vector2 src, Vector2 dest)
	{
		if (src == dest) return;
		_ForeObjects[dest.y][dest.x] = object;
		if (_ForeObjects[src.y][src.x] == object) _ForeObjects[src.y][src.x] = nullptr;
	}
#pragma endregion
	
}