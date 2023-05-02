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
		static Scene* GetActiveScene() { return mActiveScene; }
		
	private:
		static std::vector<Scene*> mScenes;
		static Scene* mActiveScene;
		static int sceneNum;
	};
}
