#include "LCamera.h"
#include "LApplication.h"
#include "LGameObject.h"
#include "LTransform.h"
#include "LInput.h"
#include "LTime.h"
#include "LImage.h"

extern cl::Application application;
namespace cl
{
	Vector2 Camera::mResolution = Vector2::Zero;
	Vector2 Camera::mLookPosition = Vector2::Zero;
	Vector2 Camera::mDistance = Vector2::Zero;
	GameObject* Camera::mTarget = nullptr;
	Image* Camera::mFilm = nullptr; 
	cl::Camera::eFilmState Camera::meFilmState = Camera::eFilmState::Idle;
	float Camera::mFilmAlpha = 0;

	void Camera::Initiailize()
	{
		mResolution.x = application.GetWidth();
		mResolution.y = application.GetHeight();
		mLookPosition = (mResolution / 2.0f);
		mFilm = Image::CreateEmptyImage(L"Film", mResolution.x, mResolution.y, RGB(0, 0, 0));
	}

	void Camera::Update()
	{

		if (Input::GetKey(eKeyCode::LEFT))
			mLookPosition.x -= 100.0f * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::RIGHT))
			mLookPosition.x += 100.0f * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::UP))
			mLookPosition.y -= 100.0f * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::DOWN))
			mLookPosition.y += 100.0f * Time::DeltaTime();


		if (mTarget != nullptr)
		{
			mLookPosition
				= mTarget->GetComponent<Transform>()->GetPos();
		}

		mDistance = mLookPosition - (mResolution / 2.0f);
	}
	void Camera::Render(HDC hdc)
	{
		if (meFilmState == FadingIn)
			FadeIn(hdc);
	}
	void Camera::Clear()
	{
		mResolution.x = application.GetWidth();
		mResolution.y = application.GetHeight();
		mLookPosition = (mResolution / 2.0f);
		mDistance = Vector2::Zero;
	}
	void Camera::StartFadeIn()
	{
		if (meFilmState == Idle)
			meFilmState = FadingIn;
	}
	void Camera::StartFadeOut()
	{
		if (meFilmState == Idle)
			meFilmState = FadingOut;
	}
	void Camera::FadeIn(HDC hdc)
	{
		const static float animationTime = 1.0f;
		static float timer = 0;
		static bool isFading = false;
		if (isFading == false)
		{
			mFilmAlpha = 255;
			isFading = true;
			timer = 0;
		}
		if (isFading)
		{
			timer += Time::DeltaTime();
			float ratio = timer / animationTime;
			mFilmAlpha = 1-ratio;
			if (timer >= animationTime)
			{
				mFilmAlpha = 0;
				isFading = false;
				meFilmState = Idle;
			}
		}
		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = 0;
		func.SourceConstantAlpha = (BYTE)(255.0f * mFilmAlpha);

		AlphaBlend(hdc, 0, 0, mResolution.x, mResolution.y, 
			mFilm->GetHdc(), 0, 0, mResolution.x, mResolution.y,
			func);
	}
	void Camera::FadeOut(HDC hdc)
	{
		const static float animationTime = 1.0f;
		static float timer = 0;
		static bool isFading = false;
		if (isFading == false)
		{
			mFilmAlpha = 255;
			isFading = true;
			timer = 0;
		}
		if (isFading)
		{
			timer += Time::DeltaTime();
			float ratio = timer / animationTime;
			mFilmAlpha = ratio;
			if (timer >= animationTime)
			{
				mFilmAlpha = 0;
				isFading = false;
				meFilmState = Idle;
			}
		}
		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = 0;
		func.SourceConstantAlpha = (BYTE)(255.0f * mFilmAlpha);

		AlphaBlend(hdc, 0, 0, mResolution.x, mResolution.y,
			mFilm->GetHdc(), 0, 0, mResolution.x, mResolution.y,
			func);
	}
}
