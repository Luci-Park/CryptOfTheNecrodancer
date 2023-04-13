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
namespace cl
{
	Monster::Monster(Scene* sc, bool isTouchingGround)
		: GameCharacter(sc, isTouchingGround)
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
		mHeart = object::Instantiate<MonsterHeart>(GameObject::GetScene(), mTransform, mTransform->GetPos() + Vector2(0, -UNITLENGTH * 0.7), eLayerType::Hearts);
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
	bool Monster::WillMove()
	{
		if(mNextDir == Vector2::Zero)
			return false;
		else
		{
			TileObject* object = MapManager::GetMonster(mNextDir + mIndex);
			if (object != nullptr && !object->WillMove())
			{
				return false;
			}
		}
		return true;
	}
	void Monster::OnAttacked(float attackPower)
	{
		GameCharacter::OnAttacked(attackPower);
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
		mSprite->Reset();
		mTransform->SetPos(mMoveTarget);
		mNextDir = Vector2::Zero;
		if (!UnSink())
		{
			Vector2 nextDir = GetNextDir();
			mSprite->Turn(nextDir);
			if (!TryAttack(nextDir) && !TryDig(nextDir))
			{
				mNextDir = nextDir;
			}
		}
	}
	void Monster::OnLateBeat()
	{
		TryMove(mNextDir);
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
			return true;
		}
		return false;
	}
	bool Monster::TryMove(Vector2 direction)
	{
		if (!WillMove()) {
			MoveFailed(direction);
			return false;
		}
		else {
			mMoveTarget += direction * UNITLENGTH;
			MapManager::Move(this, mIndex, mIndex + direction);
			mIndex += direction;
			if (direction != Vector2::Zero)
				mSprite->Jump();
			return true;
		}
	}
	void Monster::PlayOnHitSound()
	{
		mGeneralHit->Play(false);
	}
	void Monster::PlayOnDeathSound()
	{
		mGeneralDeath->Play(false);
	}
}