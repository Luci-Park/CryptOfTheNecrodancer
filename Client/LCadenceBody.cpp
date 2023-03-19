#include "LCadenceBody.h"
#include "LAnimator.h"
namespace cl
{
	const std::wstring CadenceBody::mLeftAnimation = L"CadenceLeftBody";
	const std::wstring CadenceBody::mRightAnimation = L"CadenceRightBody";
	const int CadenceBody::bodyIndex[] = { 2, 3, 4, 5, 6, 7, 9, 11 };
	CadenceBody::CadenceBody(Scene* scene)
		:GameObject(scene, false)
	{

	}
	CadenceBody::~CadenceBody()
	{
	}
	void CadenceBody::Initialize()
	{
		mAnimator = AddComponent<Animator>();

		std::wstring leftPath = L"..\\Assets\\Arts\\Player\\Cadence_Left.bmp";
		std::wstring rightPath = L"..\\Assets\\Arts\\Player\\Cadence_Right.bmp";
		mAnimator->CreateAnimation(mLeftAnimation, L"CadenceLeft", leftPath, 16, 16, 12, 2, 4, Vector2::Zero, 0.36f);
		mAnimator->CreateAnimation(mRightAnimation, L"CadenceRight", rightPath, 16, 16,0, 2, 4, Vector2::Zero, 0.36f);

		PlayRight();
		GameObject::Initialize();
	}
	void CadenceBody::Update()
	{
		if (isRight)
			PlayRight();
		else
			PlayLeft();
		GameObject::Update();
	}
	void CadenceBody::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void CadenceBody::Release()
	{
		GameObject::Release();
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