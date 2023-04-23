#include "LDragon.h"
#include "LMapManager.h"
#include "LGreenDragonSprite.h"
#include "LRedDragonSprite.h"
namespace cl
{
	GreenDragon::GreenDragon(Scene* sc)
		:DragonBase(sc)
	{
	}
	GreenDragon::~GreenDragon()
	{
	}
	void GreenDragon::Initialize()
	{
		DragonBase::Initialize();
		mSprite = object::Instantiate<GreenDragonSprite>(GameObject::GetScene(), mTransform, mTransform->GetPos(), eLayerType::Monster);
	}
	void GreenDragon::SetStats()
	{
		mActivationRadius = 0;
		mMaxHealth = 4;
		mAttackPower = 2;
		mDrop = 15;
	}
	RedDragon::RedDragon(Scene* sc)
		:DragonBase(sc)
	{
		std::wstring path = L"..\\Assets\\Audio\\SoundEffects\\Enemies\\Midboss\\Dragon\\";
		std::wstring extend = L".wav";
	}
	RedDragon::~RedDragon()
	{
	}
	void RedDragon::Initialize()
	{
		DragonBase::Initialize();
		mDragonSprite = object::Instantiate<RedDragonSprite>(GameObject::GetScene(), mTransform, mTransform->GetPos(), eLayerType::Monster);
		mSprite = mDragonSprite;
	}
	void RedDragon::SetStats()
	{
		mActivationRadius = 10;
		mMaxHealth = 6;
		mAttackPower = 3;
		mDrop = 20;
	}
	Vector2 RedDragon::GetNextDir()
	{
		if (mDragonState == State::Fire)
		{
			SetDragonState(State::Idle);
			return Vector2::Zero;
		}
		else if (mDragonState == State::ReadyFire)
		{
			SetDragonState(State::Fire);
			return Vector2::Zero;
		}
		else
		{
			Vector2 dir = RedDragon::IsInSight();
			if (Vector2::Left == dir || Vector2::Right == dir)
			{
				SetDragonState(State::ReadyFire);
				return Vector2::Zero;
			}
			else
			{
				return DragonBase::GetNextDir();
			}
		}
	}
	void RedDragon::SetDragonState(State state)
	{
		DragonBase::SetDragonState(state);
		mDragonSprite->SetDragonState(state);
	}
	Vector2 RedDragon::IsInSight()
	{
		Vector2 playerPos = MapManager::GetPlayerIndex();
		if (playerPos.y == mIndex.y)
		{
			Vector2 dir = (playerPos - mIndex).TileNormalize();
			for (int i = 1; i <= Vector2::Distance(playerPos, mIndex); ++i)
			{
				Vector2 pos = mIndex + dir * i;
				if (MapManager::GetWall(pos) != nullptr)
				{
					return Vector2::Zero;
				}
			}
			return dir;
		}
		else
			return Vector2::Zero;
	}
	void RedDragon::ShootFireball()
	{
	}
}