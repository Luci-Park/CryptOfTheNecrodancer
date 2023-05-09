#pragma once
#include "LScene.h"
namespace cl
{
	class SceneManager
	{
	public:
		static void Initialize();
		static void Update();
		static void Render(HDC hdc);
		static void Release();

		static void LoadScene(eSceneType type);
		static Scene* GetActiveScene() { return _ActiveScene; }
		
	private:
		static void LateLoadScene();

		static std::vector<Scene*> _Scenes;
		static Scene* _ActiveScene;
		static eSceneType _queuedScene;
	};
}
