#include "LTitleScene.h"
#include "LApplication.h"
#include "LSceneManager.h"
#include "LCamera.h"
#include "LInput.h"
#include "LImage.h"
#include "LAudioClip.h"
#include "LResources.h"
extern cl::Application application;
namespace cl
{

	TitleScene::TitleScene()
		: Scene(L"Title")
		, mBackground(nullptr)
		, mButton(nullptr)
		, mBGM(nullptr)
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		//mBackground = Resources::Load<Image>(L"Title", L"..\\Assets\\Arts\\Effects\\Title_Screen.bmp");
		mButton = Resources::Load<Image>(L"ButtonTitle", L"..\\Assets\\Arts\\Effects\\Title_Screen_Button.bmp");
		mBGM = Resources::Load<AudioClip>(L"1-3", L"..\\Assets\\Audio\\BGM\\Mausoleum Mash (1-3).wav");
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
	void TitleScene::OnEnter()
	{
		Camera::StartFadeIn();
		mBGM->Play(true);
	}
	void TitleScene::OnExit()
	{
		mBGM->Stop(true);
	}
}