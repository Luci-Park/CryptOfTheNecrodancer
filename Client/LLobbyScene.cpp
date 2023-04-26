#include "LLobbyScene.h"
#include "LMapManager.h"
#include "LSceneManager.h"
#include "LInput.h"
#include "LBeatManager.h"
#include "LResources.h"
#include "LAudioClip.h"
#include "LImage.h"
#include "LBishopSprite.h"
#include "LKingSprite.h"
#include "LKnightSprite.h"
#include "LPawnSprite.h"
#include "LQueenSprite.h"
#include "LRookSprite.h"
#include "LObject.h"
#include "LGrooveChain.h"
namespace cl
{
	LobbyScene::LobbyScene()
		:Scene(L"Lobby")
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
		BeatManager::Update();
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
		BeatManager::Reset();
		BeatManager::SetBPM(130);
		GrooveChainManager::Initialize();
		MapManager::CreateMap(MapManager::MapType::Lobby, this);
		mBGM->Play(true);
	}
	void LobbyScene::OnExit()
	{
		MapManager::DestroyMap();
		mBGM->Stop(true);
		Scene::OnExit();
	}
}