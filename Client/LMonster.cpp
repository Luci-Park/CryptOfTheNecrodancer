#include "LMonster.h"
#include "LCharacterSprite.h"
#include "LCadence.h"
#include "LMapManager.h"
#include "LWallTile.h"
#include "LObject.h"
#include "LMonsterWeapon.h"
#include "LResources.h"
#include "LAudioClip.h"
#include "LMonsterHeart.h"
#include "LTileLight.h"
namespace cl
{
	Monster::Monster(Scene* sc, bool isTouchingGround)
		: GameCharacter(sc, isTouchingGround)
		, mDigPower(0)
		, mAttackPower(0)
		, mDrop(0)
		, mbIsActivated(false)
		, mbIsAggroed(false)
	{
		mTransform->SetScale(Vector2::One * UNITSCALE);
		mGeneralHit = Resources::Load<AudioClip>(L"GeneralHit", L"..\\Assets\\Audio\\SoundEffects\\Enemies\\Monsters\\en_general_hit.wav");
		mGeneralDeath = Resources::Load<AudioClip>(L"GeneralHit", L"..\\Assets\\Audio\\SoundEffects\\Enemies\\Monsters\\en_general_death.wav");
		mGeneralDeath->SetVolume(100);
		mGeneralHit->SetVolume(100);
	}
	Monster::~Monster()
	{
	}
	void Monster::Initialize()
	{
		GameCharacter::Initialize();
		SetStats();
		mHealth = mMaxHealth;
		SetWeapon();
		mHeart = object::Instantiate<MonsterHeart>(GameObject::GetScene(), mTransform, mTransform->GetPos() + Vector2(0, -UNITLENGTH), eLayerType::Hearts);
		mHeart->SetHearts(mMaxHealth, mHealth);
		BeatManager::AddCharacters(this);
	}
	void Monster::Update()
	{
		GameCharacter::Update();
		
	}
	void Monster::Render(HDC hdc)
	{
		GameCharacter::Render(hdc);
	}
	void Monster::Sink()
	{
		GameCharacter::Sink(); 
	}
	void Monster::OnAttacked(float attackPower, Vector2 dir)
	{
		GameCharacter::OnAttacked(attackPower, dir);
		if (mHealth > 0)
		{
			mHeart->SetHearts(mMaxHealth, mHealth);
		}
	}
	void Monster::OnDestroy()
	{
		MapManager::DestroyTileObject(mIndex);
		//LeaveGold
	}
	void Monster::OnBeat()
	{
		CheckAggro();
		CheckActivation();
		CheckShadow();
		if (mbIsActivated || mbIsAggroed)
		{
			mMoveStatus = MoveStatus::NotMoved;
			mSprite->Reset();
			mTransform->SetPos(mMoveTarget);
			mNextDir = Vector2::Zero;
			if (!UnSink())
			{
				Vector2 nextDir = GetNextDir();
				mSprite->Turn(nextDir);
				if (nextDir == Vector2::Zero) mMoveStatus = MoveStatus::Moved;
				else if (TryAttack(nextDir)) mMoveStatus = MoveStatus::Attacked;
				else if (TryDig(nextDir)) mMoveStatus = MoveStatus::Dug;
				else
					mNextDir = nextDir;
			}
			else
			{
				mMoveStatus = MoveStatus::Unsunked;
			}
		}
	}
	void Monster::OnLateBeat()
	{
		if(mbIsActivated || mbIsAggroed)
			TryMove();
	}
	void Monster::OnBeatChanged()
	{
		GameCharacter::OnBeatChanged();
	}
	void Monster::SetWeapon()
	{
		mWeapon = object::Instantiate<MonsterWeapon>(GameObject::GetScene(), GameObject::mTransform, GameObject::mTransform->GetPos(), eLayerType::Effects);
		mWeapon->SetPower(mAttackPower);
	}
	bool Monster::TryAttack(Vector2 direction)
	{
		Cadence* player = MapManager::GetPlayer(mIndex + direction);
		if (player)
		{
			mWeapon->Attack(mIndex, direction);
			PlayOnAttackSound();
			Recoil(direction);
			return true;
		}
		
		return false;
	}
	bool Monster::TryDig(Vector2 direction)
	{
		WallTile* wall = MapManager::GetWall(mIndex + direction);
		if (wall)
		{
			bool success = wall->OnDig(mDigPower);
			Recoil(direction);
			return true;
		}
		return false;
	}
	bool Monster::TryMove()
	{
		if (mMoveStatus != MoveStatus::NotMoved) return false;
		TileObject* object = MapManager::GetTileObject(mIndex + mNextDir);
		if (object != nullptr && object != this)
		{
			mMoveStatus = MoveStatus::IsAsking;
			if (!object->TryMove())
			{
				Recoil(mNextDir);
				mMoveStatus = MoveStatus::Failed;
				return false;
			}
		}
		mMoveStatus = MoveStatus::Moved;
		mMoveTarget += mNextDir * UNITLENGTH;
		MapManager::Move(this, mIndex, mIndex + mNextDir);
		mIndex += mNextDir;
		if (mNextDir != Vector2::Zero)
			mSprite->Jump();
		return true;
	}
	void Monster::PlayOnHitSound()
	{
		mGeneralHit->Play(false);
	}
	void Monster::PlayOnDeathSound()
	{
		mGeneralDeath->Play(false);
	}
	void Monster::CheckAggro()
	{
		if (mbIsAggroed) return;
		TileLight* light = MapManager::GetLight(mIndex);
		if (light != nullptr && light->IsRevealed() && IsNearPlayer())
		{
			mbIsAggroed = true;
			OnAggroed();
		}
	}
	void Monster::CheckActivation()
	{		
		Vector2 playerPos = MapManager::GetPlayerIndex();
		mbIsActivated = Vector2::Distance(playerPos, mIndex) <= mActivationRadius;
	}
	void Monster::CheckShadow()
	{
		TileLight* light = MapManager::GetLight(mIndex);
		if (light != nullptr)
		{
			if (!light->IsRevealed())
				mSprite->SetActive(false);
			else
			{
				mSprite->SetActive(true);
				mSprite->SetShadow(!(light->IsInSight() && light->Illumination() > 0.6f));
			}
		}
	}
	bool Monster::IsNearPlayer()
	{
		Vector2 playerPos = MapManager::GetPlayerIndex();
		return(playerPos.x - 10 <= mIndex.x && mIndex.x < playerPos.x + 10
			&& playerPos.y - 6 <= mIndex.y && mIndex.y < playerPos.y + 6);
	}
}