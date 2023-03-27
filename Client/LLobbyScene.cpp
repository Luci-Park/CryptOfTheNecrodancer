#include "LLobbyScene.h"
#include "LMapManager.h"
#include "LSceneManager.h"
#include "LInput.h"
namespace cl
{
	LobbyScene::LobbyScene()
		:Scene(L"Lobby")
	{
	}
	LobbyScene::~LobbyScene()
	{
		MapManager::DestroyMap();
		Scene::Destroy();
	}
	void LobbyScene::Initialize()
	{
		Scene::Initialize();
	}
	void LobbyScene::Update()
	{
		Scene::Update();
		if (Input::GetKeyDown(eKeyCode::Q))
			SceneManager::LoadScene(eSceneType::Splash);
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