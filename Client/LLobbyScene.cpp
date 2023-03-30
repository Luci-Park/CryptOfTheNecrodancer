#include "LLobbyScene.h"
#include "LMapManager.h"
#include "LSceneManager.h"
#include "LInput.h"
#include "LBeatManager.h"
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
		BeatManager::Update();
		Scene::Update();
		if (Input::GetKeyDown(eKeyCode::Q))
			SceneManager::LoadScene(eSceneType::Splash);
	}
	void LobbyScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void LobbyScene::OnEnter()
	{
		BeatManager::Reset();
		MapManager::CreateMap(MapManager::MapType::Lobby, this);
		BeatManager::SetBPM(130);
	}
	void LobbyScene::OnExit()
	{
		MapManager::DestroyMap();
		Scene::OnExit();
	}
}