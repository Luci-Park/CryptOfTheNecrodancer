#include "LSplashScene.h"
#include "LImage.h"
#include "LResources.h"
#include "LCamera.h"
#include "LApplication.h"
#include "LInput.h"
#include "LSceneManager.h"
#include "LTime.h"
extern cl::Application application;
namespace cl
{
	SplashScene::SplashScene()
		:Scene(L"Splash")
		, mImage(nullptr)
		, mTimer(0.0f)
	{
	}
	SplashScene::~SplashScene()
	{
	}
	void SplashScene::Initialize()
	{
		Camera::StartFadeIn();
		mImage = Resources::Load<Image>(L"Warning", L"..\\Assets\\Arts\\Effects\\Warning_Screen.bmp");
	}
	void SplashScene::Update()
	{
		mTimer += Time::DeltaTime();
		if(mTimer >= 5.0f || Input::GetKeyDown(eKeyCode::ENTER))
		{
			SceneManager::LoadScene(eSceneType::Title);
		}
	}
	void SplashScene::Render(HDC hdc)
	{
		TransparentBlt(hdc, 0, 0, application.GetWidth(), application.GetHeight(), mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));
	}
	void SplashScene::Destroy()
	{
	}
	void SplashScene::OnEnter()
	{
		mTimer = 0;
	}
	void SplashScene::OnExit()
	{
	}
}