#include "LLobbyScene.h"
#include "LMapManager.h"

namespace cl
{
	LobbyScene::LobbyScene()
		:Scene(L"Lobby")
	{
	}
	LobbyScene::~LobbyScene()
	{
	}
	void LobbyScene::Initialize()
	{
		Scene::Initialize();
	}
	void LobbyScene::Update()
	{
		Scene::Update();
	}
	void LobbyScene::OnEnter()
	{
		MapManager::CreateMap(MapManager::MapType::Lobby, this);
	}
	void LobbyScene::OnExit()
	{
		MapManager::DestroyMap();
		Scene::Destroy();
	}
}