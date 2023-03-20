#include "LTutorialScene.h"
#include "LObject.h"
#include "LApplication.h"
#include "LCadence.h"
#include "LGameManager.h"
extern cl::Application application;
namespace cl
{
	TutorialScene::TutorialScene()
		:Scene(L"Tutorial")
		, mGameManager(nullptr)
	{
	}
	TutorialScene::~TutorialScene()
	{
	}
	void TutorialScene::Initialize()
	{
		Scene::Initialize();
		mGameManager = object::Instantiate<GameManager>(this, Vector2::Zero, eLayerType::System);
		mGameManager->SetBPM(100);
		Cadence* cadence = object::Instantiate<Cadence>(this, application.GetCenter(), eLayerType::Player);
		cadence->SetManager(mGameManager);
		cadence->OnBeatChanged();
	}
	void TutorialScene::Update()
	{
		Scene::Update();
	}
	void TutorialScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void TutorialScene::Destroy()
	{
		Scene::Destroy();
	}
	void TutorialScene::Release()
	{
		mGameManager = nullptr;
		Scene::Release();
	}
	void TutorialScene::OnEnter()
	{
		Scene::OnEnter();
	}
	void TutorialScene::OnExit()
	{
		Scene::OnExit();
	}
}