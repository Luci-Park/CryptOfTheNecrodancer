#include "LCadenceBody.h"
#include "LAnimator.h"
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
		mAnimator->CreateAnimation(mLeftAnimation, L"CadenceLeft", leftPath, 16, 16, 12, 2, 4, Vector2::Zero, 0.36f);
		mAnimator->CreateAnimation(mRightAnimation, L"CadenceRight", rightPath, 16, 16,0, 2, 4, Vector2::Zero, 0.36f);

		PlayRight();
	}
	void CadenceBody::Update()
	{
		if(Vector2::Right == mDir)
			PlayRight();
		else if(-Vector2::Right == mDir)
			PlayLeft();
		GameObject::Update();
	}
	void CadenceBody::Render(HDC hdc)
	{
		GameObject::Render(hdc);
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
		//mAnimator->SetPercent(Vector2(1.0f, 0.25f));
	}
	void CadenceBody::UnSink()
	{
		//mAnimator->SetPercent(Vector2::One);
	}
	void CadenceBody::PlayRight()
	{
		if (!mAnimator->IsAnimationPlaying(mRightAnimation))
			mAnimator->Play(mRightAnimation, true, false);
	}

	void CadenceBody::PlayLeft()
	{
		if (!mAnimator->IsAnimationPlaying(mLeftAnimation))
			mAnimator->Play(mLeftAnimation, true, true);
	}
}