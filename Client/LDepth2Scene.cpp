#include "LDepth2Scene.h"
#include "LMapManager.h"
#include "LBeatManager.h"
#include "LResources.h"
#include "LAudioClip.h"
#include "LGrooveChain.h"
namespace cl
{
	Depth2Scene::Depth2Scene()
		:Scene(eSceneType::Depth1)
		, mBGM(nullptr)
	{
	}
	Depth2Scene::~Depth2Scene()
	{
		MapManager::DestroyMap();
	}
	void Depth2Scene::Initialize()
	{
		mBGM = Resources::Load<AudioClip>(L"1-2", L"..\\Assets\\Audio\\BGM\\Crypteque (1-2).wav");
		Scene::Initialize();
	}
	void Depth2Scene::Update()
	{
		BeatManager::Update();
		MapManager::Update();
		Scene::Update();
	}
	void Depth2Scene::Render(HDC hdc)
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
	void Depth2Scene::OnEnter()
	{
		Scene::OnEnter();
		BeatManager::Reset();
		BeatManager::SetBPM(130);
		MapManager::CreateMap(MapManager::MapType::Random, this);
		mBGM->Play(true);
	}
	void Depth2Scene::OnExit()
	{
		mBGM->Stop(true);
		Scene::OnExit();
	}
}