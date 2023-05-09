#include "LWeapon.h"
#include "LAnimator.h"
#include "LConductor.h"
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
		mSpriteRenderer = AddComponent<SpriteRenderer>();
		mSpriteRenderer->SetImage(L"Weapons", L"..\\Assets\\Arts\\Items\\Weapons.bmp");
		SetSprite();
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
	bool Weapon::Attack(Vector2 srcIdx, Vector2 input)
	{
		bool success = TryAttack(srcIdx, input);
		if (success)
		{
			PlayAttackAnimation(input);
		}
		return success;
	}
}