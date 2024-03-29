#include "LScene.h"
#include "LSceneManager.h"
#include "LMapManager.h"

namespace cl
{
	Scene::Scene(eSceneType type)
		:mType(type)
	{
		mLayers.reserve((UINT)eLayerType::Size);
		mLayers.resize((UINT)eLayerType::Size);
	}
	Scene::~Scene()
	{
		
	}
	void Scene::Initialize()
	{
	}
	void Scene::Update()
	{
		for (int i =0; i < mLayers.size(); i++)
		{
			mLayers[i].Update();
		}
	}
	void Scene::Render(HDC hdc)
	{
		for (int i = 0; i < (UINT)eLayerType::Size; ++i)
		{
			mLayers[i].Render(hdc);
		}
	}

	void Scene::Destroy(GameObject* object)
	{
		for (Layer& layer : mLayers)
		{
			if (layer.Destroy(object))
				return;
		}
	}

	void Scene::OnEnter()
	{
	}
	void Scene::OnExit()
	{
		for (int i = 0; i < mLayers.size(); ++i)
		{
			mLayers[i].Release();
		}
	}
	void Scene::AddGameObject(GameObject* obj, eLayerType layer)
	{
		mLayers[(UINT)layer].AddGameObject(obj);
	}
	std::vector<GameObject*>& Scene::GetGameObjects(eLayerType layer)
	{
		return mLayers[(UINT)layer].GetGameObjects();
	}
}
