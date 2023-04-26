#pragma once
#include "LGameObject.h"
#include "LScene.h"
#include "LSceneManager.h"
#include "LTransform.h"

namespace cl::object
{
	template <typename T>
	static inline T* Instantiate(Scene* sc, eLayerType type)
	{
		T* gameObj = new T(sc);
		Scene* scene = sc;
		scene->AddGameObject(gameObj, type);
		gameObj->Initialize();
		return gameObj;
	}

	template <typename T>
	static inline T* Instantiate(Scene* sc, Vector2 pos, eLayerType type)
	{
		T* gameObj = new T(sc);
		Scene* scene = sc;
		scene->AddGameObject(gameObj, type);
		gameObj->mTransform->SetPos(pos);
		gameObj->Initialize();
		return gameObj;
	}

	template <typename T>
	static inline T* Instantiate(Scene* sc, Transform* parent, Vector2 pos, eLayerType type)
	{
		T* gameObj = new T(sc);
		gameObj->mTransform->SetParent(parent);
		sc->AddGameObject(gameObj, type);
		gameObj->mTransform->SetPos(pos);
		gameObj->Initialize();
		return gameObj;
	}
	template <typename T>
	static inline T* Instantiate(eLayerType type)
	{
		Scene* scene = SceneManager::GetActiveScene();
		T* gameObj = new T(scene);
		scene->AddGameObject(gameObj, type);
		gameObj->Initialize();
		return gameObj;
	}

	template <typename T>
	static inline T* Instantiate(Vector2 pos, eLayerType type)
	{
		Scene* scene = SceneManager::GetActiveScene();
		T* gameObj = new T(scene);
		scene->AddGameObject(gameObj, type);
		gameObj->Initialize();
		gameObj->mTransform->SetPos(pos);
		return gameObj;
	}
}