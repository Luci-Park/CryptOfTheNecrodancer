#include "LTitleScene.h"
#include "LCamera.h"
#include "LImage.h"
#include "LResources.h"
#include "LInput.h"
#include "LSceneManager.h"
#include "LApplication.h"

extern cl::Application application;
namespace cl
{

	TitleScene::TitleScene()
		: Scene(L"Title")
		, mBackground(nullptr)
		, mButton(nullptr)
		, timer(0.0f)
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		//mBackground = Resources::Load<Image>(L"Title", L"..\\Assets\\Arts\\Effects\\Title_Screen.bmp");
		mButton = Resources::Load<Image>(L"ButtonTitle", L"..\\Assets\\Arts\\Effects\\Title_Screen_Button.bmp");
	}
	void TitleScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::ENTER))
		{
			SceneManager::LoadScene(eSceneType::Lobby);
		}
	}
	void TitleScene::Render(HDC hdc)
	{
		TransparentBlt(hdc, 0, 0, application.GetWidth(), application.GetHeight(), mButton->GetHdc(), 0, 0, mButton->GetWidth(), mButton->GetHeight(), RGB(255, 0, 255));
	}
	void TitleScene::Destroy()
	{
		Scene::Destroy();
	}
	void TitleScene::OnEnter()
	{
		Camera::StartFadeIn();
	}
	void TitleScene::OnExit()
	{
	}
}