#include "LMinotaurBase.h"
#include "LMapManager.h"
#include "LWallTile.h"
#include "LMinotaurSprite.h"
#include "LMonsterMelee.h"
namespace cl
{
	MinotaurBase::MinotaurBase(Scene* sc)
		:Monster(sc, true)
		, mBeatCount(0)
		, mMinoState(State::Idle)
	{
		mSize = 2;
		mDigPower = 2;
		mLightSource = new LightSource(mTransform, 1.0, 1.0);
		std::wstring path = L"..\\Assets\\Audio\\SoundEffects\\Enemies\\Midboss\\Minotaur\\";
		std::wstring extend = L".wav";
		mAttackSound = Resources::Load<AudioClip>(L"en_minotaur_attack", path + L"en_minotaur_attack" + extend);
		mDeathSound = Resources::Load<AudioClip>(L"en_minotaur_death", path + L"en_minotaur_death" + extend);
		mChargeSound = Resources::Load<AudioClip>(L"en_minotaur_charge", path + L"en_minotaur_charge" + extend);
		mWallImpactSound = Resources::Load<AudioClip>(L"en_minotaur_wallimpact", path + L"en_minotaur_wallimpact" + extend);
		mCrySound = Resources::Load<AudioClip>(L"en_minotaur_cry", path + L"en_minotaur_cry" + extend);
		std::wstring key = L"en_minotaur_hit_0";
		for (int i = 0; i < 3; ++i)
		{
			std::wstring newKey = key + std::to_wstring(i + 1);
			mHitSounds[i] = Resources::Load<AudioClip>(newKey, path + newKey + extend);
		}
	}
	MinotaurBase::~MinotaurBase()
	{
		delete mLightSource;
		mLightSource = nullptr;
	}
	void MinotaurBase::Initialize()
	{
		Monster::Initialize();
		mMinoSprite = object::Instantiate<MinotaurSprite>(GameObject::GetScene(), mTransform, mTransform->GetPos(), eLayerType::Monster);
		mMinoSprite->SetY(GetY());
		mSprite = mMinoSprite;
	}
	void MinotaurBase::OnAggroed()
	{
		mCrySound->Play(false);
	}
	void MinotaurBase::OnLateBeat()
	{
		Monster::OnLateBeat();
		if(mMoveState != MoveState::Failed)
			mBeatCount++;
	}
	bool MinotaurBase::TryDig(Vector2 direction)
	{
		if (mMinoState != State::Charge)
			return Monster::TryDig(direction);
		WallTile* wall = MapManager::GetWall(mIndex + direction);
		if (wall)
		{
			bool success = wall->OnDig(mDigPower);
			ChangeState(State::Faint);
			return true;
		}
		return false;
	}
	bool MinotaurBase::TryAttack(Vector2 direction)
	{
		Cadence* player = MapManager::GetPlayer(mIndex + direction);
		if (player)
		{
			mWeapon->Attack(mIndex, direction);
			PlayOnAttackSound();
			ChangeState(State::Faint);
			return true;
		}

		return false;
	}
	void MinotaurBase::PlayOnAttackSound()
	{
		mAttackSound->Play(false);
	}
	void MinotaurBase::PlayOnHitSound()
	{
		int idx = GetRandomInt(0, 2);
		mHitSounds[idx] ->Play(false);
		Monster::PlayOnHitSound();
	}
	void MinotaurBase::PlayOnDeathSound()
	{
		mDeathSound->Play(false);
		Monster::PlayOnDeathSound();
	}
	Vector2 MinotaurBase::GetNextDir()
	{
		if (mMinoState == State::Faint)
		{
			if (mBeatCount == 3)
			{
				ChangeState(State::Idle);
				return Vector2::Zero;
			}
		}
		Vector2 chargeDir;
		if (mMinoState == State::Idle)
		{
			mDigPower = 2;
			chargeDir = IsInSight();
			if (Vector2::IsCardinal(chargeDir))
			{
				ChangeState(State::Charge);
			}
			else
			{
				if(mBeatCount % 2)
					return CardinalMoveTowards();
				return Vector2::Zero;
			}
		}
		if (mMinoState == State::Charge)
		{
			mDigPower = 5;
			if(chargeDir != Vector2::Zero)
				return chargeDir;
			return mPrevDir;
		}
		return Vector2::Zero;
	}
	Vector2 MinotaurBase::IsInSight()
	{
		Vector2 playerPos = MapManager::GetPlayerIndex();
		Vector2 dir = (playerPos - mIndex).TileNormalize();
		if (Vector2::IsCardinal(dir))
		{
			float distance = Vector2::Distance(playerPos, mIndex);
			if (distance <= 5)
			{
				for (int i = 1; i <= distance; ++i)
				{
					if (MapManager::GetWall(mIndex + dir * i) != nullptr ||
						MapManager::GetEnemy(mIndex + dir * i) != nullptr)
					{
						return Vector2::Zero;
					}
				}
				return dir;
			}
		}
		return Vector2::Zero;
	}
	void MinotaurBase::ChangeState(State state)
	{
		if (state != mMinoState)
		{
			mMinoState = state;
			mBeatCount = 0;
			//alert animation;
			mMinoSprite->SetMinoState(state);
			if (State::Charge == state)
				mChargeSound->Play(false);
			else if (State::Faint == state)
				mWallImpactSound->Play(false);
		}
	}
}
