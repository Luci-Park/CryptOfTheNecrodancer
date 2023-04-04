#include "LWeapon.h"
#include "LAnimator.h"
#include "LBeatManager.h"
namespace cl
{
	Weapon::Weapon(Scene* sc)
		:GameObject(sc, false)
	{

	}
	Weapon::~Weapon()
	{
	}
	void Weapon::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		SetAnimation();
		GameObject::Initialize();
	}
	void Weapon::Update()
	{
		GameObject::Update();
	}
	void Weapon::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Weapon::OnBeatChanged()
	{
		mAnimator->SetDuration(BeatManager::BeatDuration() * 0.25);
	}
	void Weapon::PlayAttackAnimation(Vector2 dir)
	{
		mTransform->SetLocalPos(EffectPos(dir));
		mAnimator->Play(SelectAnimation(dir), false, false);
	}
	bool Weapon::Attack(TileObject* object, Vector2 srcIdx, Vector2 input)
	{
		bool success = TryAttack(object, srcIdx, input);
		if (success)
			PlayAttackAnimation(input);
		return success;
	}
}