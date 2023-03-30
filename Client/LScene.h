#pragma once
#include "LEntity.h"
#include "LLayer.h"

namespace cl
{
	class Scene : public Entity
	{
	public:
		Scene(const std::wstring& name);
		virtual ~Scene();
		
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Destroy(GameObject* object);

		virtual void OnEnter();
		virtual void OnExit();

		void AddGameObject(GameObject* obj, eLayerType layer);
		std::vector<GameObject*>& GetGameObjects(eLayerType layer);

	protected:
		std::vector<Layer> mLayers;
	};
}
