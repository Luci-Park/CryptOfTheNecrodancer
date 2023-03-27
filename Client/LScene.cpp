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

	void Scene::Destroy()
	{
		std::vector<GameObject*> deleteGameObjects = {};
		for (Layer& layer : mLayers)
		{
			std::vector<GameObject*>&  gameObjects
				= layer.GetGameObjects();

			for (std::vector<GameObject*>::iterator iter = gameObjects.begin()
				; iter != gameObjects.end() ; )
			{
				if ((*iter)->GetState() == GameObject::eState::Death)
				{
					deleteGameObjects.push_back((*iter));
					iter = gameObjects.erase(iter);
				}
				else
				{
					iter++;
				}
			}
		}
		for (int i = 0; i < deleteGameObjects.size(); ++i)
		{
			delete deleteGameObjects[i];
			deleteGameObjects[i] = nullptr;
		}
	}

	void Scene::OnEnter()
	{
	}
	void Scene::OnExit()
	{
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
