//#include "LTutorialScene.h"
//#include "LObject.h"
//#include "LApplication.h"
//#include "LCadence.h"
//#include "LGameManager.h"
//#include "LInput.h"
//extern cl::Application application;
//namespace cl
//{
//	TutorialScene::TutorialScene()
//		:Scene(L"Tutorial")
//		, mGameManager(nullptr)
//	{
//	}
//	TutorialScene::~TutorialScene()
//	{
//	}
//	void TutorialScene::Initialize()
//	{
//		Scene::Initialize();
//		BeatManager::SetBPM(100);
//		mGameManager = object::Instantiate<BeatManager>(this, Vector2::Zero, eLayerType::System);
//		Cadence* cadence = object::Instantiate<Cadence>(this, application.GetCenter(), eLayerType::Player);
//		mGameManager->AddCharacters(cadence);
//	}
//	void TutorialScene::Update()
//	{
//		if (Input::GetKeyDown(eKeyCode::O))
//		{
//			BeatManager::SetBPM(BeatManager::BPM() + 50);
//		}
//		Scene::Update();
//	}
//}