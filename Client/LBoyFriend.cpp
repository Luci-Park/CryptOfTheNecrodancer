#include "LBoyfriend.h"
#include "LAnimator.h"
#include "LInput.h"
#include "LTime.h"
namespace cl
{
	const std::wstring Boyfriend::animationPath[] = {
		L"..\\FNFAssets\\Art\\24Bit\\Characters\\Boyfriend\\Idle",
		L"..\\FNFAssets\\Art\\24Bit\\Characters\\Boyfriend\\Up",
		L"..\\FNFAssets\\Art\\24Bit\\Characters\\Boyfriend\\Down",
		L"..\\FNFAssets\\Art\\24Bit\\Characters\\Boyfriend\\Left",
		L"..\\FNFAssets\\Art\\24Bit\\Characters\\Boyfriend\\Right",
		L"..\\FNFAssets\\Art\\24Bit\\Characters\\Boyfriend\\Up_Bad",
		L"..\\FNFAssets\\Art\\24Bit\\Characters\\Boyfriend\\Down_Bad",
		L"..\\FNFAssets\\Art\\24Bit\\Characters\\Boyfriend\\Left_Bad",
		L"..\\FNFAssets\\Art\\24Bit\\Characters\\Boyfriend\\Right_Bad",
	};
	const std::wstring Boyfriend::animation[] = {
		L"BoyfriendIdle",
		L"BoyfriendUp",
		L"BoyfriendDown",
		L"BoyfriendLeft",
		L"BoyfriendRight",
		L"BoyfriendUpBad",
		L"BoyfriendDownBad",
		L"BoyfriendLeftBad",
		L"BoyfriendRightBad",
	};
	Boyfriend::Boyfriend()
		:GameObject(false)
	{

	}
	Boyfriend::~Boyfriend()
	{
	}
	void Boyfriend::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		for (int i = 0; i < (UINT)eBFState::Size; ++i)
		{
			float dur = 0.1f;
			if (i > (UINT)eBFState::Right)
				dur = 0.3f;
			mAnimator->CreateAnimations(animationPath[i], animation[i], Vector2::Zero, dur);
		}
		mState = eBFState::Idle;
		mAnimator->Play(L"BoyfriendIdle", true);


		GameObject::Initialize();
	}
	void Boyfriend::Update()
	{
		if (Input::GetKeyDown(eKeyCode::W))
		{
			mState = Up;
			OnKeyDown();
		}
		else if (Input::GetKeyUp(eKeyCode::W))
		{
			OnKeyUp();
		}

		if (Input::GetKeyDown(eKeyCode::A))
		{
			mState = Left;
			OnKeyDown();
		}
		else if (Input::GetKeyUp(eKeyCode::A))
		{
			OnKeyUp();
		}
		if (Input::GetKeyDown(eKeyCode::S))
		{
			mState = Down;
			OnKeyDown();
		}
		else if (Input::GetKeyUp(eKeyCode::S))
		{
			OnKeyUp();
		}

		if (Input::GetKeyDown(eKeyCode::D))
		{
			mState = Right;
			OnKeyDown();
		}
		else if (Input::GetKeyUp(eKeyCode::D))
		{
			OnKeyUp();
		}
		if (Input::GetKeyDown(eKeyCode::Q))
		{
			mState = UpBad;
			OnKeyDown();
		}
		else if (Input::GetKeyUp(eKeyCode::Q))
		{
			OnKeyUp();
		}

		if (Input::GetKeyDown(eKeyCode::E))
		{
			mState = LeftBad;
			OnKeyDown();
		}
		else if (Input::GetKeyUp(eKeyCode::E))
		{
			OnKeyUp();
		}
		if (Input::GetKeyDown(eKeyCode::R))
		{
			mState = DownBad;
			OnKeyDown();
		}
		else if (Input::GetKeyUp(eKeyCode::R))
		{
			OnKeyUp();
		}

		if (Input::GetKeyDown(eKeyCode::T))
		{
			mState = RightBad;
			OnKeyDown();
		}
		else if (Input::GetKeyUp(eKeyCode::T))
		{
			OnKeyUp();
		}
		GameObject::Update();
	}
	void Boyfriend::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Boyfriend::Release()
	{
		GameObject::Release();
	}
	void Boyfriend::OnIdle()
	{
		mState = Idle;
		mAnimator->Play(animation[eBFState::Idle], true);
	}
	void Boyfriend::OnKeyDown()
	{
		if(!mAnimator->IsAnimationPlaying(animation[(UINT)mState]))
			mAnimator->Play(animation[(UINT)mState], true);
	}
	void Boyfriend::OnKeyUp()
	{
		OnIdle();
		/*
		if(mAnimator->IsAnimationPlaying(animation[(UINT)mState - 8]))
			mAnimator->Play(animation[(UINT)mState], false);*/
	}
	void Boyfriend::Move()
	{
		Vector2 pos = mTransform->GetPos();
		if (Input::GetKey(eKeyCode::A))
			pos.x -= 100.0f * Time::DeltaTime();
		
		if (Input::GetKey(eKeyCode::D))
			pos.x += 100.0f * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::W))
			pos.y -= 100.0f * Time::DeltaTime();
		if (Input::GetKey(eKeyCode::S))
			pos.y += 100.0f * Time::DeltaTime();

		mTransform->SetPos(pos);
	}
	void Boyfriend::BFWriteFile()
	{
		HANDLE hFile = CreateFile(
			L"example.txt",          // file name
			GENERIC_WRITE,          // access mode
			0,                      // sharing mode (not used for file creation)
			NULL,                   // security attributes
			CREATE_ALWAYS,          // creation disposition (always create a new file)
			FILE_ATTRIBUTE_NORMAL,  // file attributes (no special attributes)
			NULL);                  // template file (not used for file creation)

		if (hFile == INVALID_HANDLE_VALUE)
		{
			// hande error
			return;
		}
		Vector2 pos = mTransform->GetPos();
		char buf[1024];
		sprintf_s(buf, sizeof(buf), "%d %d", (int)pos.x, (int)pos.y);
		DWORD bytesWritten;
		WriteFile(hFile, buf, strlen(buf), &bytesWritten, NULL);

		CloseHandle(hFile);
	}
}