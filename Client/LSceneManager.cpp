#include "LSceneManager.h"
#include "LCollisionManager.h"
#include "LCamera.h"
#include "LSceneIncludes.h"
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
		//mScenes[(UINT)eSceneType::Tutorial] = new TutorialScene();
		mScenes[(UINT)eSceneType::Lobby] = new LobbyScene();
		mScenes[(UINT)eSceneType::Depth1] = new Depth1Scene();
		mScenes[(UINT)eSceneType::Depth2] = new Depth2Scene();
		mScenes[(UINT)eSceneType::Depth3] = new Depth3Scene();
		
		for ( Scene* scene : mScenes )
		{
			if (scene == nullptr)
				continue;

			scene->Initialize();
		}
		LoadScene(eSceneType::Lobby);
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
	}

	void SceneManager::Render(HDC hdc)
	{
		mActiveScene->Render(hdc);
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
		if(mActiveScene != nullptr)
			mActiveScene->OnExit();
		CollisionManager::Clear();
		mActiveScene = mScenes[(UINT)type];
		mActiveScene->OnEnter();		
	}
}
