#include "LCadenceHead.h"
#include "LAnimator.h"
#include "LConductor.h"
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
		GameObject::Initialize();
		mAnimator = AddComponent<Animator>();

		std::wstring leftPath = L"..\\Assets\\Arts\\Player\\Cadence_Left.bmp";
		std::wstring rightPath = L"..\\Assets\\Arts\\Player\\Cadence_Right.bmp";
		mAnimator->CreateAnimation(mLeftAnimation, L"CadenceLeft", leftPath, 16, 16, 12, 0, 4, -Vector2(12, 24), Conductor::Instance().SecondsPerBeat());
		mAnimator->CreateAnimation(mRightAnimation, L"CadenceRight", rightPath, 16, 16, 0, 0, 4, -Vector2(12, 24), Conductor::Instance().SecondsPerBeat());

		PlayRight();
	}
	void CadenceHead::Flip(Vector2 dir)
	{
		if (dir == Vector2::Left || dir == Vector2::Right)
			mDir = dir;
		if (mDir == Vector2::Right)
			PlayRight();
		else if (mDir == Vector2::Left)
			PlayLeft();
	}
	void CadenceHead::Reset()
	{
		mAnimator->Reset();
	}

	void CadenceHead::SetDuration(float dur)
	{
		mAnimator->SetDuration(dur);
	}

	void CadenceHead::PlayRight()
	{
		mAnimator->Play(mRightAnimation, Animator::PlaySetting::Loop, false);
	}

	void CadenceHead::PlayLeft()
	{
		mAnimator->Play(mLeftAnimation, Animator::PlaySetting::Loop, true);
	}
	
}