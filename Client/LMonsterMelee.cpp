#include "LMonsterWeapon.h"
#include "LAnimator.h"
#include "LTileObject.h"
#include "LMapManager.h"
#include "LCadence.h"
#include "LMonsterMeleeEffect.h"
#include "LObject.h"
namespace cl
{
	MonsterMelee::MonsterMelee(Scene* sc)
		:Weapon(sc)
	{
	}

	MonsterMelee::~MonsterMelee()
	{
	}

	void MonsterMelee::SetAnimation()
	{
		mEffect = object::Instantiate<MonsterMeleeEffect>(GameObject::GetScene(), mTransform, mTransform->GetPos(), eLayerType::Effects);
		OnBeatChanged();
	}

	void MonsterMelee::SetSprite()
	{
	}

	void MonsterMelee::OnBeatChanged()
	{
		mEffect->OnBeatChanged();
	}

	bool MonsterMelee::TryAttack(Vector2 srcIdx, Vector2 input)
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

	void MonsterMelee::PlayAttackAnimation(Vector2 dir)
	{
		mEffect->PlayEffect(dir);
	}
}
