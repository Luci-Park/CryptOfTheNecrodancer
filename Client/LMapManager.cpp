#include "LMapManager.h"
#include "LMap.h"
namespace cl
{
#pragma region MapManager
	Map* MapManager::_Map = nullptr;
	void MapManager::CreateMap(MapType type, Scene* sc)
	{
		DestroyMap();
		switch (type)
		{
		default:
		case Lobby:
			_Map = new LobbyMap();
		}
		_Map->CreateMap(sc);
	}
	void MapManager::DestroyMap()
	{
		if (_Map != nullptr)
		{
			delete _Map;
			_Map = nullptr;
		}
	}
	void MapManager::DestroyTileObject(Vector2 index)
	{
		_Map->DestroyTileObject(index);
	}
	void MapManager::DestroyWallObject(Vector2 index)
	{
		_Map->DestroyWallObject(index);
	}
	void MapManager::Update()
	{
		_Map->Update();
	}
	void MapManager::Render(HDC hdc)
	{
		_Map->Render(hdc);
	}
	void MapManager::OnTileStep(TileObject* object, Vector2 pos)
	{
		_Map->OnTileStep(object, pos);
	}
	WallTile* MapManager::GetWall(Vector2 index)
	{
		return _Map->GetWall(index);
	}
	TileObject* MapManager::GetTileObject(Vector2 index)
	{
		return _Map->GetTileObject(index);
	}
	Cadence* MapManager::GetPlayer(Vector2 index)
	{
		return _Map->GetPlayer(index);
	}
	Vector2 MapManager::GetPlayerIndex()
	{
		return _Map->GetPlayerIndex();
	}
	Item* MapManager::GetItem(Vector2 index)
	{
		return _Map->GetItem(index);
	}
	Vector2 MapManager::SetItem(Item* item, Vector2 pos)
	{
		return _Map->SetItem(item, pos);
	}
	void MapManager::PlayerMove(TileObject* object, Vector2 src, Vector2 dest)
	{
		_Map->PlayerMove(object, src, dest);
	}
	void MapManager::Move(TileObject* object, Vector2 src, Vector2 dest)
	{
		_Map->Move(object, src, dest);
	}
#pragma endregion
	
}