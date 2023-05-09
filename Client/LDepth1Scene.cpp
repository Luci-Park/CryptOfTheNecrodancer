#include "LDepth1Scene.h"
#include "LMapManager.h"
#include "LConductor.h"
#include "LResources.h"
#include "LAudioClip.h"
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
		if (!Conductor::Instance().IsPlaying())	Conductor::Instance().Play();
		Conductor::Instance().Update();
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
		Conductor::Instance().SetSong(mBGM, 115);
		MapManager::CreateMap(MapManager::MapType::Random1, this);
	}
	void Depth1Scene::OnExit()
	{
		Conductor::Instance().Stop();
		Scene::OnExit();
	}
}