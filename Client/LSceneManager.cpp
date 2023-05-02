#include "LSceneManager.h"
#include "LCollisionManager.h"
#include "LCamera.h"
#include "LSceneIncludes.h"
namespace cl
{	
	//SceneManager scsene;
	//SceneManager* scsene = new SceneManager();
	std::vector<Scene*> SceneManager::_Scenes = {};
	Scene* SceneManager::_ActiveScene = nullptr;
	eSceneType SceneManager::_queuedScene = eSceneType::Size;
	void SceneManager::Initialize()
	{
		_Scenes.resize((UINT)eSceneType::Size);

		_Scenes[(UINT)eSceneType::Splash] = new SplashScene();
		_Scenes[(UINT)eSceneType::Title] = new TitleScene();
		_Scenes[(UINT)eSceneType::Lobby] = new LobbyScene();
		_Scenes[(UINT)eSceneType::Depth1] = new Depth1Scene();
		_Scenes[(UINT)eSceneType::Depth2] = new Depth2Scene();
		_Scenes[(UINT)eSceneType::Depth3] = new Depth3Scene();
		_Scenes[(UINT)eSceneType::BossRoom] = new BossScene();
		
		for ( Scene* scene : _Scenes )
		{
			if (scene == nullptr)
				continue;

			scene->Initialize();
		}
		LoadScene(eSceneType::Lobby);
	}

	void SceneManager::Update()
	{
		if(_ActiveScene != nullptr)
			_ActiveScene->Update();
		LateLoadScene();
	}

	void SceneManager::Render(HDC hdc)
	{
		if(_ActiveScene != nullptr)
			_ActiveScene->Render(hdc);
	}
	
	void SceneManager::Release()
	{
		for (int i = 0; i < (UINT)eSceneType::Size; ++i)
		{
			if (_Scenes[i] == nullptr)
				continue;
			delete _Scenes[i];
			_Scenes[i] = nullptr;
		}
	}

	void SceneManager::LoadScene(eSceneType type)
	{
		_queuedScene = type;
	}
	void SceneManager::LateLoadScene()
	{
		if (_queuedScene == eSceneType::Size) return;
		Camera::Clear();
		if (_ActiveScene != nullptr)
			_ActiveScene->OnExit();
		CollisionManager::Clear();
		_ActiveScene = _Scenes[(UINT)_queuedScene];
		_ActiveScene->OnEnter();
		_queuedScene = eSceneType::Size;
	}
}
