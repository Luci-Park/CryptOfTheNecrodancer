#include "LLobbyScene.h"
#include "LMapManager.h"
#include "LConductor.h"
#include "LConductor.h"
#include "LResources.h"
#include "LAudioClip.h"
#include "LGrooveChain.h"
#include "LCadence.h"
namespace cl
{
	LobbyScene::LobbyScene()
		:Scene(eSceneType::Lobby)
		, mBGM(nullptr)
	{
	}
	LobbyScene::~LobbyScene()
	{
		MapManager::DestroyMap();
	}
	void LobbyScene::Initialize()
	{
		mBGM = Resources::Load<AudioClip>(L"Lobby", L"..\\Assets\\Audio\\BGM\\Rhythmortis (Lobby).wav");
		Scene::Initialize();
	}
	void LobbyScene::Update()
	{
		if (!Conductor::Instance().IsPlaying())	Conductor::Instance().Play();
		Conductor::Instance().Update();
		MapManager::Update();
		Scene::Update();
	}
	void LobbyScene::Render(HDC hdc)
	{
		for (int i = 0; i < (UINT)eLayerType::Size; ++i)
		{
			if (i == (UINT)eLayerType::Player)
				MapManager::Render(hdc);
			else if (i == (UINT)eLayerType::Monster || i == (UINT)eLayerType::Wall)
				continue;
			else
				mLayers[i].Render(hdc);
		}
	}

	void LobbyScene::OnEnter()
	{
		Scene::OnEnter();
		Cadence::Reset();
		Conductor::Instance().SetSong(mBGM, 130);
		GrooveChainManager::Initialize();
		MapManager::CreateMap(MapManager::MapType::Lobby, this);
	}
	void LobbyScene::OnExit()
	{
		Conductor::Instance().Stop();
		Scene::OnExit();
	}
}