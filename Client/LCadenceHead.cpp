#include "LCadenceHead.h"
#include "LAnimator.h"
namespace cl
{
	const std::wstring CadenceHead::mLeftAnimation = L"CadenceLeftHead";
	const std::wstring CadenceHead::mRightAnimation = L"CadenceRightHead";
	CadenceHead::CadenceHead(Scene* scene)
		:GameObject(scene, false)
		, mAnimator(nullptr)
	{

	}
	CadenceHead::~CadenceHead()
	{
	}
	void CadenceHead::Initialize()
	{
		mAnimator = AddComponent<Animator>();

		std::wstring leftPath = L"..\\Assets\\Arts\\Player\\Cadence_Left.bmp";
		std::wstring rightPath = L"..\\Assets\\Arts\\Player\\Cadence_Right.bmp";
		mAnimator->CreateAnimation(mLeftAnimation, L"CadenceLeft", leftPath, 16, 16, 12, 0, 4, Vector2::Zero, 0.36f);
		mAnimator->CreateAnimation(mRightAnimation, L"CadenceRight", rightPath, 16, 16, 0, 0, 4, Vector2::Zero, 0.36f);

		PlayRight();
		GameObject::Initialize();
	}
	void CadenceHead::Update()
	{
		if (isRight)
			PlayRight();
		else
			PlayLeft();
		GameObject::Update();
	}
	void CadenceHead::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void CadenceHead::Release()
	{
		GameObject::Release();
	}

	void CadenceHead::PlayRight()
	{
		if(!mAnimator->IsAnimationPlaying(mRightAnimation))
			mAnimator->Play(mRightAnimation, true, false);
	}

	void CadenceHead::PlayLeft()
	{
		if (!mAnimator->IsAnimationPlaying(mLeftAnimation))
			mAnimator->Play(mLeftAnimation, true, true);
	}
	
}