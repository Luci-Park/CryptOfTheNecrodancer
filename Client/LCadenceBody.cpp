#include "LCadenceBody.h"
#include "LAnimator.h"
#include "LConductor.h"

namespace cl
{
	const std::wstring CadenceBody::mLeftAnimation = L"CadenceLeftBody";
	const std::wstring CadenceBody::mRightAnimation = L"CadenceRightBody";
	const int CadenceBody::bodyIndex[] = { 2, 3, 4, 5, 6, 7, 9, 11 };
	CadenceBody::CadenceBody(Scene* scene)
		:GameObject(scene, false)
		, mAnimator(nullptr)
	{

	}
	CadenceBody::~CadenceBody()
	{
	}
	void CadenceBody::Initialize()
	{
		GameObject::Initialize();
		mAnimator = AddComponent<Animator>();

		std::wstring leftPath = L"..\\Assets\\Arts\\Player\\Cadence_Left.bmp";
		std::wstring rightPath = L"..\\Assets\\Arts\\Player\\Cadence_Right.bmp";
		mAnimator->CreateAnimation(mLeftAnimation, L"CadenceLeft", leftPath, 16, 16, 12, 2, 4, -Vector2(12, 24), Conductor::Instance().SecondsPerBeat());
		mAnimator->CreateAnimation(mRightAnimation, L"CadenceRight", rightPath, 16, 16,0, 2, 4, -Vector2(12, 24), Conductor::Instance().SecondsPerBeat());
	
		PlayRight();
	}
	void CadenceBody::Flip(Vector2 dir)
	{
		if (dir == Vector2::Left || dir == Vector2::Right)
			mDir = dir;
		if (mDir == Vector2::Right)
			PlayRight();
		else if (mDir == Vector2::Left)
			PlayLeft();
	}
	void CadenceBody::Reset()
	{
		mAnimator->Reset();
	}
	void CadenceBody::SetDuration(float dur)
	{
		mAnimator->SetDuration(dur);
	}
	void CadenceBody::Sink()
	{
		mAnimator->SetPercent({ 1.0f, 0.72f });
	}
	void CadenceBody::UnSink()
	{
		mAnimator->SetPercent(Vector2::One);
	}
	void CadenceBody::Flash()
	{
	}
	void CadenceBody::PlayRight()
	{
		mAnimator->Play(mRightAnimation, Animator::PlaySetting::Loop, false);
	}

	void CadenceBody::PlayLeft()
	{
		mAnimator->Play(mLeftAnimation, Animator::PlaySetting::Loop, true);
	}
}