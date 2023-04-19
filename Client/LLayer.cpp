#include "LLayer.h"


namespace cl
{
	Layer::Layer()
	{
	}
	Layer::~Layer()
	{
		Release();
	}
	void Layer::Initialize()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj != nullptr && gameObj->IsActive())
				gameObj->Initialize();
		}
	}
	void Layer::Update()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj != nullptr && gameObj->IsActive())
				gameObj->Update();
		}
	}
	void Layer::Render(HDC hdc)
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if(gameObj != nullptr && gameObj->IsActive())
				gameObj->Render(hdc);
		}
	}

	bool Layer::Destroy(GameObject* object)
	{
		auto it = std::find(mGameObjects.begin(), mGameObjects.end(), object);
		if (it != mGameObjects.end())
		{
			mGameObjects.erase(it);
			delete object;
			return true;
		}
		return false;
	}

	void Layer::Release()
	{
		for (int i = 0; i < mGameObjects.size(); ++i)
		{
			delete mGameObjects[i];
			mGameObjects[i] = nullptr;
		}
	}
	
	void Layer::AddGameObject(GameObject* gameObj)
	{
		if (gameObj == nullptr)
			return;

		mGameObjects.push_back(gameObj);
	}
}
