#include "LDragonFireball.h"
#include "LObject.h"
#include "LMapManager.h"
#include "LTileObject.h"

namespace cl
{
	DragonFireball::DragonFireball(Scene* sc)
		:Weapon(sc)
	{
		mPower = 5;
	}
	DragonFireball::~DragonFireball()
	{
	}
	void DragonFireball::SetAnimation()
	{
	}
	void DragonFireball::SetSprite()
	{
	}
	void DragonFireball::OnBeatChanged()
	{
		for (int i = 0; i < mFireballEffects.size(); ++i)
		{
			mFireballEffects[i]->OnBeatChanged();
		}
	}
	bool DragonFireball::TryAttack(Vector2 srcIdx, Vector2 input)
	{
		length = 0;
		while(true)
		{
			Vector2 index = srcIdx + input * (length + 1);
			if (MapManager::GetWall(index))
				break;
			else
			{
				TileObject* to = MapManager::GetTileObject(index);
				if (to != nullptr)
					to->OnAttacked(mPower, input);
				length++;
			}
		}
		return true;
	}
	void DragonFireball::PlayAttackAnimation(Vector2 dir)
	{
		for (int i = 0; i < length; ++i)
		{
			if (i >= mFireballEffects.size())
			{
				FireballEffect* mf = object::Instantiate<FireballEffect>(GameObject::GetScene(), mTransform, mTransform->GetPos(), eLayerType::Effects);
				mf->SetIndex(i);
				mFireballEffects.push_back(mf);
			}
			mFireballEffects[i]->PlayEffect(dir);
		}
	}
}
