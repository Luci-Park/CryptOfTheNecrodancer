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
		enum class eState
		{
			Active,
			Pause,
			Death,
		};

		GameObject(Scene* scene, bool isUI);
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

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
		
		eState GetState() { return mState; }
		void SetState(eState state) { mState = state; }
		
		Scene* GetScene(){ return mScene; }
		bool IsUI() { return mbisUI; }
	public:
		Transform* mTransform;
	private:
		std::vector<Component*> mComponents;
		eState mState;
		bool mbisUI;
		Scene* mScene;
	};
}