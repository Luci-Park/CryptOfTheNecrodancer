#include "LCadenceAttackEffect.h"
#include "LAnimator.h"
#include "LGameManager.h"
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
			3, 1, 0, 0, 3, Vector2::Zero, GameManager::BeatDuration() * 0.25);
		mAnimator->CreateAnimation(L"Dagger_Left", L"Dagger_Left", L"..\\Assets\\Arts\\Effects\\AttackSwipes\\Dagger_Left.bmp",
			3, 1, 0, 0, 3, Vector2::Zero, GameManager::BeatDuration() * 0.25);
		mAnimator->CreateAnimation(L"Dagger_Up", L"Dagger_Up", L"..\\Assets\\Arts\\Effects\\AttackSwipes\\Dagger_Up.bmp",
			1, 3, 0, 0, 3, Vector2::Zero, GameManager::BeatDuration() * 0.25);
		mAnimator->CreateAnimation(L"Dagger_Down", L"Dagger_Down", L"..\\Assets\\Arts\\Effects\\AttackSwipes\\Dagger_Down.bmp",
			1, 3, 0, 0, 3, Vector2::Zero, GameManager::BeatDuration() * 0.25);
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
		mAnimator->SetDuration(GameManager::BeatDuration() * 0.25);
	}

	void CadenceAttackEffect::Attack(Vector2 dir)
	{
		if (dir == Vector2::Right)
		{
			mTransform->SetLocalPos(Vector2::Right * GameManager::UnitLength());
			mAnimator->Play(L"Dagger_Right", false, false);
		}
		if (dir == Vector2::Left)
		{
			mTransform->SetLocalPos(Vector2::Left * GameManager::UnitLength());
			mAnimator->Play(L"Dagger_Left", false, false);
		}
		if (dir == Vector2::Up)
		{
			mTransform->SetLocalPos(Vector2::Up * GameManager::UnitLength());
			mAnimator->Play(L"Dagger_Up", false, false);
		}
		if (dir == Vector2::Down)
		{
			mTransform->SetLocalPos(Vector2::Down * GameManager::UnitLength());
			mAnimator->Play(L"Dagger_Down", false, false);
		}
	}
}