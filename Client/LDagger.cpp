#include "LDagger.h"
#include "LTileObject.h"
#include "LMapManager.h"
#include "LObject.h"
#include "LShortMeleeEffect.h"
#include "LSpriteRenderer.h"
namespace cl
{
	Dagger::Dagger(Scene* sc)
		:Weapon(sc)
	{
		mPower = 1;
	}

	Dagger::~Dagger()
	{
	}

	void Dagger::SetAnimation()
	{
		mEffect = object::Instantiate<ShortMeleeEffect>(GameObject::GetScene(), mTransform, mTransform->GetPos(), eLayerType::Effects);
		OnBeatChanged();
	}

	void Dagger::SetSprite()
	{
		//SetSprite
	}

	void Dagger::OnBeatChanged()
	{
		mEffect->OnBeatChanged();
	}

	bool Dagger::TryAttack(Vector2 srcIdx, Vector2 input)
	{
		Vector2 dest = srcIdx + input;
		TileObject* enemy = MapManager::GetEnemy(dest);
		if (enemy != nullptr)
		{
			enemy->OnAttacked(mPower);
			return true;
		}
		return false;
	}

	void Dagger::PlayAttackAnimation(Vector2 dir)
	{
		mEffect->PlayEffect(dir);
	}

}
