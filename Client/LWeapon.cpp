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
		SetAnimation();
		mSpriteRenderer = AddComponent<SpriteRenderer>();
		mAnimator = AddComponent<Animator>();
		mSpriteRenderer->SetImage(L"Weapons", L"..\\Assets\\Arts\\Items\\Weapons.bmp");
		SetSprite();
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