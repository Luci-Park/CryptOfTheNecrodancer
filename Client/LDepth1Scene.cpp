#include "LDepth1Scene.h"
#include "LMapManager.h"
#include "LBeatManager.h"
#include "LResources.h"
#include "LAudioClip.h"
#include "LGrooveChain.h"
namespace cl
{
	Depth1Scene::Depth1Scene()
		:Scene(eSceneType::Depth1)
		, mBGM(nullptr)
	{
	}
	Depth1Scene::~Depth1Scene()
	{
		MapManager::DestroyMap();
	}
	void Depth1Scene::Initialize()
	{
		mBGM = Resources::Load<AudioClip>(L"1-1", L"..\\Assets\\Audio\\BGM\\Disco Descent (1-1).wav");
		Scene::Initialize();
	}
	void Depth1Scene::Update()
	{
		BeatManager::Update();
		MapManager::Update();
		Scene::Update();
	}
	void Depth1Scene::Render(HDC hdc)
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
	void Depth1Scene::OnEnter()
	{
		Scene::OnEnter();
		BeatManager::Reset();
		BeatManager::SetBPM(115);
		GrooveChainManager::Initialize();
		MapManager::CreateMap(MapManager::MapType::Random, this);
		mBGM->Play(true);
	}
	void Depth1Scene::OnExit()
	{
		MapManager::DestroyMap();
		mBGM->Stop(true);
		Scene::OnExit();
	}
}