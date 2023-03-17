#include "LTutorialScene.h"
#include "LObject.h"
#include "LApplication.h"
#include "LCadence.h"
extern cl::Application application;
namespace cl
{
	TutorialScene::TutorialScene()
		:Scene(L"Tutorial")
	{
	}
	TutorialScene::~TutorialScene()
	{
	}
	void TutorialScene::Initialize()
	{
		object::Instantiate<Cadence>(this, application.GetCenter(), eLayerType::Player);
		/*bf = object::Instantiate<Boyfriend>(this, application.GetCenter(), eLayerType::Player);
		object::Instantiate<StageBG>(this, application.GetCenter(), eLayerType::BG);
		object::Instantiate<ArrowUI>(this, application.GetCenter(), eLayerType::UI);*/
		Scene::Initialize();
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