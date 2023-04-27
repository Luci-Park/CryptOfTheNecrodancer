#include "LMonsterWeapon.h"
#include "LAnimator.h"
#include "LTileObject.h"
#include "LMapManager.h"
#include "LCadence.h"
#include "LMonsterMeleeEffect.h"
#include "LObject.h"
namespace cl
{
	MonsterWeapon::MonsterWeapon(Scene* sc)
		:Weapon(sc)
	{
	}

	MonsterWeapon::~MonsterWeapon()
	{
	}

	void MonsterWeapon::SetAnimation()
	{
		mEffect = object::Instantiate<MonsterMeleeEffect>(GameObject::GetScene(), mTransform, mTransform->GetPos(), eLayerType::Effects);
		OnBeatChanged();
	}

	void MonsterWeapon::SetSprite()
	{
	}

	void MonsterWeapon::OnBeatChanged()
	{
		mEffect->OnBeatChanged();
	}

	bool MonsterWeapon::TryAttack(Vector2 srcIdx, Vector2 input)
	{
		Vector2 dest = srcIdx + input;
		Cadence* enemy = MapManager::GetPlayer(dest);
		if (enemy != nullptr)
		{
			enemy->OnAttacked(mPower, input);
			return true;
		}
		return false;
	}

	void MonsterWeapon::PlayAttackAnimation(Vector2 dir)
	{
		mEffect->PlayEffect(dir);
	}
}
