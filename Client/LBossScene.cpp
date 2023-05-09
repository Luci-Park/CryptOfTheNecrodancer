#include "LBossScene.h"
#include "LMapManager.h"
#include "LConductor.h"
#include "LResources.h"
#include "LAudioClip.h"
#include "LGrooveChain.h"
namespace cl
{
	BossScene::BossScene()
		: Scene(eSceneType::BossRoom)
		, mBGM(nullptr)
	{
	}
	BossScene::~BossScene()
	{
		MapManager::DestroyMap();
	}
	void BossScene::Initialize()
	{
		mBGM = Resources::Load<AudioClip>(L"DeepBlues", L"..\\Assets\\Audio\\BGM\\Knight to C-Sharp (Deep Blues).wav");
		Scene::Initialize();
	}
	void BossScene::Update()
	{
		if (!Conductor::Instance().IsPlaying())	Conductor::Instance().Play();
		Conductor::Instance().Update();
		MapManager::Update();
		Scene::Update();
	}
	void BossScene::Render(HDC hdc)
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
	void BossScene::OnEnter()
	{
		Scene::OnEnter();
		Conductor::Instance().SetSong(mBGM, 123);
		MapManager::CreateMap(MapManager::MapType::DeepBlues, this);
	}
	void BossScene::OnExit()
	{
		Conductor::Instance().Stop();
		Scene::OnExit();
	}
}