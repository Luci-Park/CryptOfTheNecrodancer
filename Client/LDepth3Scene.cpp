#include "LDepth3Scene.h"
#include "LMapManager.h"
#include "LConductor.h"
#include "LResources.h"
#include "LAudioClip.h"
#include "LGrooveChain.h"
namespace cl
{
	Depth3Scene::Depth3Scene()
		:Scene(eSceneType::Depth1)
		, mBGM(nullptr)
	{
	}
	Depth3Scene::~Depth3Scene()
	{
		MapManager::DestroyMap();
	}
	void Depth3Scene::Initialize()
	{
		mBGM = Resources::Load<AudioClip>(L"1-3", L"..\\Assets\\Audio\\BGM\\Mausoleum Mash (1-3).wav");
		Scene::Initialize();
	}
	void Depth3Scene::Update()
	{
		if (!Conductor::Instance().IsPlaying())	Conductor::Instance().Play();
		Conductor::Instance().Update();
		MapManager::Update();
		Scene::Update();
	}
	void Depth3Scene::Render(HDC hdc)
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
	void Depth3Scene::OnEnter()
	{
		Scene::OnEnter();
		Conductor::Instance().SetSong(mBGM, 140);
		MapManager::CreateMap(MapManager::MapType::Random3, this);
	}
	void Depth3Scene::OnExit()
	{
		Conductor::Instance().Stop();
		Scene::OnExit();
	}
	
}