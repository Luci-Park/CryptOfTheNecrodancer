#include "LScene.h"
#include "LSceneManager.h"


namespace cl
{
	Scene::Scene(const std::wstring& name)
	{
		SetName(name);
		mLayers.reserve((UINT)eLayerType::Size);
		mLayers.resize((UINT)eLayerType::Size);
	}
	Scene::~Scene()
	{
		
	}
	void Scene::Initialize()
	{
		SceneManager::SetActiveScene(this);
		
	}
	void Scene::Update()
	{
		for (Layer& layer : mLayers)
		{
			layer.Update();
		}
	}
	void Scene::Render(HDC hdc)
	{
		for (Layer& layer : mLayers)
		{
			layer.Render(hdc);
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
