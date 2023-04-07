#include "LWeapon.h"
#include "LAnimator.h"
#include "LBeatManager.h"
#include "LCamera.h"
#include "LCadence.h"
#include "LResources.h"
#include "LAudioClip.h"
namespace cl
{
	Weapon::Weapon(Scene* sc)
		: Item(sc, eItemTypes::Weapon)
		, mbIsMelee(true)
	{
		mGetItemClip = Resources::Load<AudioClip>(L"sfx_pickup_weapon"
			, L"..\\Assets\\Audio\\SoundEffects\\SFX\\sfx_pickup_weapon.wav");
	}
	Weapon::~Weapon()
	{
	}
	void Weapon::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		SetAnimation();
		Item::Initialize();
	}
	void Weapon::Update()
	{
		Item::Update();
	}
	void Weapon::Render(HDC hdc)
	{
		Item::Render(hdc);
	}
	bool Weapon::Use(Cadence* player)
	{
		Vector2 src = player->GetPos();
		Vector2 input = player->GetInput();
		return Attack(src, input);
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
	bool Weapon::Attack(Vector2 srcIdx, Vector2 input)
	{
		bool success = TryAttack(srcIdx, input);
		if (success)
		{
			PlayAttackAnimation(input);
			Camera::StartShake();
		}
		return success;
	}
}