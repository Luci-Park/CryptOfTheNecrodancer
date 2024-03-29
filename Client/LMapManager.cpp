#include "LMapManager.h"
#include "LMapIncludes.h"

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
			break;
		case Random1:
			_Map = new RandomMap(1);
			break;
		case Random2:
			_Map = new RandomMap(2);
			break;
		case Random3:
			_Map = new RandomMap(3);
			break;
		case DeepBlues:
			_Map = new DeepBluesMap();
		}
		_Map->CreateMap(sc);
	}
	void MapManager::SetKey(TileObject* object)
	{
		if (_Map != nullptr)
			_Map->SetKey(object);
	}
	void MapManager::DestroyMap()
	{
		if (_Map != nullptr)
		{
			delete _Map;
			_Map = nullptr;
		}
	}
	void MapManager::DestroyTileObject(Vector2 index, TileObject* object)
	{
		if(_Map != nullptr)
			_Map->DestroyTileObject(index, object);
	}
	void MapManager::DestroyWallObject(Vector2 index)
	{
		if (_Map != nullptr)
			_Map->DestroyWallObject(index);
	}
	void MapManager::Update()
	{
		if (_Map != nullptr)
			_Map->Update();
	}
	void MapManager::Render(HDC hdc)
	{
		if (_Map != nullptr)
			_Map->Render(hdc);
	}
	void MapManager::AddLightSource(LightSource* light)
	{
		if (_Map != nullptr)
			_Map->AddLightSource(light);
	}
	void MapManager::RemoveLightSource(LightSource* light)
	{
		if (_Map != nullptr)
			_Map->RemoveLightSource(light);
	}
	void MapManager::SetLight(Vector2 index, float brightness)
	{
		if (_Map != nullptr)
			_Map->SetLight(index, brightness);
	}
	TileLight* MapManager::GetLight(Vector2 index)
	{
		if (_Map != nullptr)
			return _Map->GetLight(index);
		return nullptr;
	}
	void MapManager::OnTileStep(TileObject* object, Vector2 pos)
	{
		if (_Map != nullptr)
			_Map->OnTileStep(object, pos);
	}
	WallTile* MapManager::GetWall(Vector2 index)
	{
		if (_Map != nullptr)
			return _Map->GetWall(index);
		return nullptr;
	}
	TileObject* MapManager::GetEnemy(Vector2 index)
	{
		if (_Map != nullptr)
			return _Map->GetEnemy(index);
		return nullptr;
	}
	TileObject* MapManager::GetTileObject(Vector2 index)
	{
		if (_Map != nullptr)
			return _Map->GetTileObject(index);
		return nullptr;
	}
	bool MapManager::IsTileEmptyExceptPlayer(Vector2 index)
	{
		if (GetEnemy(index) == nullptr && GetWall(index) == nullptr)
			return true;
		return false;
	}
	Cadence* MapManager::GetPlayerOnIndex(Vector2 index)
	{
		if (_Map != nullptr)
			return _Map->GetPlayerOnIndex(index);
		return nullptr;
	}
	Cadence* MapManager::GetPlayer()
	{
		if (_Map != nullptr)
			return _Map->GetPlayer();
		return nullptr;
	}
	Vector2 MapManager::GetPlayerIndex()
	{
		if (_Map != nullptr)
			return _Map->GetPlayerPos();
		return Vector2();
	}
	Item* MapManager::GetItem(Vector2 index)
	{
		if (_Map != nullptr)
			return _Map->GetItem(index);
		return nullptr;
	}
	Vector2 MapManager::SetItem(Item* item, Vector2 pos)
	{
		if (_Map != nullptr)
			return _Map->SetItem(item, pos);
		return Vector2();
	}
	void MapManager::PlayerMove(TileObject* object, Vector2 src, Vector2 dest)
	{
		if (_Map != nullptr)
			_Map->PlayerMove(object, src, dest);
	}
	void MapManager::Move(TileObject* object, Vector2 src, Vector2 dest)
	{
		if (_Map != nullptr)
			_Map->Move(object, src, dest);
	}
	bool MapManager::IndexIsValid(Vector2 index)
	{
		if (_Map != nullptr)
			return _Map->IndexIsValid(index);
		return false;
	}
#pragma endregion
	
}