#pragma once
#include "LEntity.h"
#include "LComponent.h"
#include "LTransform.h"

namespace cl
{
	class Scene;
	class GameObject : public Entity
	{
	public:

		GameObject(Scene* scene, bool isUI);
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void Destroy();

		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();
			UINT compType = (UINT)comp->GetType();
			mComponents[compType] = comp;
			comp->SetOwner(this);

			return comp;
		}

		template <typename T>
		T* GetComponent()
		{
			for (Component* comp : mComponents)
			{
				if (dynamic_cast<T*>(comp))
					return dynamic_cast<T*>(comp);
			}

			return nullptr;
		}
		
		Scene* GetScene(){ return mScene; }
		bool IsUI() { return mbisUI; }
	public:
		Transform* mTransform;
	private:
		std::vector<Component*> mComponents;
		bool mbisUI;
		Scene* mScene;
	};
}
