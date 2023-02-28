#include "LApplication.h"
#include "LSceneManager.h"
#include "LTime.h"
#include "LInput.h"
namespace ci
{
	Application::Application()
		: mHwnd(NULL)
		, mHdc(NULL)
	{
	}

	Application::~Application()
	{
	}

	void Application::Initialize(HWND hWnd)
	{
		mHwnd = hWnd;
		mHdc = GetDC(hWnd);
		mWidth = 1600;
		mHeight = 900;

		RECT rect = { 0, 0, mWidth, mHeight };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		SetWindowPos(mHwnd, nullptr,
			100, 50,
			rect.right - rect.left,
			rect.bottom - rect.top,
			0);
		ShowWindow(hWnd, true);

		mBackBuffer = CreateCompatibleBitmap(mHdc, mWidth, mHeight);
		mBackHDC = CreateCompatibleDC(mHdc);

		HBITMAP defaultBitmap = (HBITMAP)SelectObject(mBackHDC, mBackBuffer);
		DeleteObject(defaultBitmap);

		Time::Initiailize();
		Input::Initialize();
		SceneManager::Initialize();
	}

	void Application::Run()
	{
		Update();
		Render();
	}

	void Application::Update()
	{
		Time::Update();
		Input::Update();
		SceneManager::Update();
		std::wstring title = SceneManager::GetActiveScene()->GetName();
		std::wstring fps = std::to_wstring((UINT)Time::FPS());
		title += L" - FPS : " + fps;
		SetWindowText(mHwnd, title.c_str());
	}

	void Application::Render()
	{
		Clear();

		Time::Render(mHdc);
		Input::Render(mHdc);
		SceneManager::Render(mHdc);

		BitBlt(mHdc, 0, 0, mWidth, mHeight, mBackHDC, 0, 0, SRCCOPY);
	}
	void Application::Release()
	{
		SceneManager::Release();
	}
	void Application::Clear()
	{
		HBRUSH blackBrush = CreateSolidBrush(RGB(0, 0, 0));
		HBRUSH oldBrush = (HBRUSH)SelectObject(mBackHDC, blackBrush);
		Rectangle(mBackHDC, -1, -1, mWidth, mHeight);
		SelectObject(mBackHDC, oldBrush);
		DeleteObject(blackBrush);
	}
}