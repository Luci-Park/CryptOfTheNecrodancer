#include "LSceneManager.h"
#include "LCollisionManager.h"
#include "LCamera.h"
#include "LSplashScene.h"
#include "LTitleScene.h"
#include "LTutorialScene.h"
namespace cl
{	
	//SceneManager scsene;
	//SceneManager* scsene = new SceneManager();
	std::vector<Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;
	int SceneManager::sceneNum = 0;
	void SceneManager::Initialize()
	{
		mScenes.resize((UINT)eSceneType::Size);

		mScenes[(UINT)eSceneType::Splash] = new SplashScene();
		mScenes[(UINT)eSceneType::Title] = new TitleScene();
		mScenes[(UINT)eSceneType::Tutorial] = new TutorialScene();
		for ( Scene* scene : mScenes )
		{
			if (scene == nullptr)
				continue;

			scene->Initialize();
		}

		mActiveScene = mScenes[(UINT)eSceneType::Splash];
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
	}

	void SceneManager::Render(HDC hdc)
	{
		mActiveScene->Render(hdc);
	}

	void SceneManager::Destroy()
	{
		mActiveScene->Destroy();
	}

	void SceneManager::Release()
	{
		for (int i = 0; i < (UINT)eSceneType::Size; ++i)
		{
			if (mScenes[i] == nullptr)
				continue;
			delete mScenes[i];
			mScenes[i] = nullptr;
		}
	}

	void SceneManager::LoadScene(eSceneType type)
	{
		Camera::Clear();
		mActiveScene->OnExit();
		CollisionManager::Clear();
		mActiveScene = mScenes[(UINT)type];
		//Camera::StartFadeIn();
		mActiveScene->OnEnter();		
	}
}
