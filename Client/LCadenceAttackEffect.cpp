#include "LCadenceAttackEffect.h"
#include "LAnimator.h"
#include "LConductor.h"
namespace cl
{
	CadenceAttackEffect::CadenceAttackEffect(Scene* sc)
		: GameObject(sc, false)
		, mAnimator(nullptr)
	{
	}
	CadenceAttackEffect::~CadenceAttackEffect()
	{
	}
	void CadenceAttackEffect::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Dagger_Right", L"Dagger_Right", L"..\\Assets\\Arts\\Effects\\AttackSwipes\\Dagger_Right.bmp",
			3, 1, 0, 0, 3, Vector2::Zero, Conductor::Instance().SecondsPerBeat() * 0.25);
		mAnimator->CreateAnimation(L"Dagger_Left", L"Dagger_Left", L"..\\Assets\\Arts\\Effects\\AttackSwipes\\Dagger_Left.bmp",
			3, 1, 0, 0, 3, Vector2::Zero, Conductor::Instance().SecondsPerBeat() * 0.25);
		mAnimator->CreateAnimation(L"Dagger_Up", L"Dagger_Up", L"..\\Assets\\Arts\\Effects\\AttackSwipes\\Dagger_Up.bmp",
			1, 3, 0, 0, 3, Vector2::Zero, Conductor::Instance().SecondsPerBeat() * 0.25);
		mAnimator->CreateAnimation(L"Dagger_Down", L"Dagger_Down", L"..\\Assets\\Arts\\Effects\\AttackSwipes\\Dagger_Down.bmp",
			1, 3, 0, 0, 3, Vector2::Zero, Conductor::Instance().SecondsPerBeat() * 0.25);
		GameObject::Initialize();
	}

	void CadenceAttackEffect::Update()
	{
		GameObject::Update();
	}

	void CadenceAttackEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void CadenceAttackEffect::OnBeatChanged()
	{
		mAnimator->SetDuration(Conductor::Instance().SecondsPerBeat() * 0.25);
	}

	void CadenceAttackEffect::OnAttack(Vector2 dir)
	{
		if (dir == Vector2::Right)
		{
			mTransform->SetLocalPos(Vector2::Right * UNITLENGTH);
			mAnimator->Play(L"Dagger_Right", Animator::PlaySetting::Once, false);
		}
		if (dir == Vector2::Left)
		{
			mTransform->SetLocalPos(Vector2::Left * UNITLENGTH);
			mAnimator->Play(L"Dagger_Left", Animator::PlaySetting::Once, false);
		}
		if (dir == Vector2::Up)
		{
			mTransform->SetLocalPos(Vector2::Up * UNITLENGTH);
			mAnimator->Play(L"Dagger_Up", Animator::PlaySetting::Once, false);
		}
		if (dir == Vector2::Down)
		{
			mTransform->SetLocalPos(Vector2::Down * UNITLENGTH);
			mAnimator->Play(L"Dagger_Down", Animator::PlaySetting::Once, false);
		}
	}
}