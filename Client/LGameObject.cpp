#include "LGameObject.h"
#include "LTransform.h"
#include "LScene.h"

namespace cl
{
	GameObject::GameObject(Scene* scene, bool isUI)
		: mScene(scene)
		, mbisUI(isUI)
	{
		mComponents.resize((UINT)eComponentType::Size);
		mTransform = AddComponent<Transform>();
	}

	GameObject::~GameObject()
	{
		for (Component* comp : mComponents)
		{
			delete comp;
			comp = nullptr;
		}
	}

	void GameObject::Initialize()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr || !comp->IsActive())
				continue;

			comp->Initialize();
		}
	}

	void GameObject::Update()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr || !comp->IsActive())
				continue;

			comp->Update();
		}
	}

	void GameObject::Render(HDC hdc)
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr || !comp->IsActive())
				continue;

			comp->Render(hdc);
		}
	}
	void GameObject::OnCollisionEnter(Collider* other)
	{
	}
	void GameObject::OnCollisionStay(Collider* other)
	{
	}
	void GameObject::OnCollisionExit(Collider* other)
	{
	}
	void GameObject::Destroy()
	{
		mScene->Destroy(this);
	}
}
