#include "LLobbyScene.h"
#include "LMapManager.h"
#include "LSceneManager.h"
#include "LInput.h"
#include "LGameManager.h"
namespace cl
{
	LobbyScene::LobbyScene()
		:Scene(L"Lobby")
	{
	}
	LobbyScene::~LobbyScene()
	{
		MapManager::DestroyMap();
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
		GameManager::SetBPM(130);
	}
	void LobbyScene::OnExit()
	{
		MapManager::DestroyMap();
		Scene::OnExit();
	}
}