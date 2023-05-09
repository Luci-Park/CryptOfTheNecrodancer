#include "LWeaponEffect.h"
#include "LAnimator.h"
#include "LConductor.h"
namespace cl
{
	WeaponEffect::WeaponEffect(Scene* sc)
		:GameObject(sc, false)
	{
	}
	WeaponEffect::~WeaponEffect()
	{
	}
	void WeaponEffect::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		GameObject::Initialize();
	}
	void WeaponEffect::Update()
	{
		GameObject::Update();
	}
	void WeaponEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void WeaponEffect::PlayEffect(Vector2 direction)
	{
		if (direction == Vector2::Up)
			PlayUp();
		else if (direction == Vector2::Down)
			PlayDown();
		else if (direction == Vector2::Left)
			PlayLeft();
		else if (direction == Vector2::Right)
			PlayRight();
	}
	void WeaponEffect::OnBeatChanged()
	{
		mAnimator->SetDuration(Conductor::Instance().SecondsPerBeat() * 0.25);
	}
}