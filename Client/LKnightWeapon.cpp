#include "LKnightWeapon.h"
#include "LKnightEffect.h"
#include "LObject.h"
namespace cl
{
	KnightWeapon::KnightWeapon(Scene* sc)
		:MonsterWeapon(sc)
	{
	}
	KnightWeapon::~KnightWeapon()
	{
	}
	void KnightWeapon::SetAnimation()
	{
		mEffect = object::Instantiate<KnightEffect>(GameObject::GetScene(), mTransform, mTransform->GetPos(), eLayerType::Effects);
		OnBeatChanged();
	}
	void KnightWeapon::SetSprite()
	{
	}
	void KnightWeapon::OnBeatChanged()
	{
		mEffect->OnBeatChanged();
	}
	void KnightWeapon::PlayAttackAnimation(Vector2 dir)
	{
		mEffect->PlayEffect(dir);
	}
}