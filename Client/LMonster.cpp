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
		SetWeapon();
		mHeart = object::Instantiate<MonsterHeart>(GameObject::GetScene(), mTransform, mTransform->GetPos(), eLayerType::Effects);
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
		//mTransform->SetPos(mMoveTarget);
		if (!UnSink())
		{
			Vector2 nextDir = GetNextDir();
			mSprite->Turn(nextDir);
			if (!TryAttack(nextDir) && !TryDig(nextDir))
			{
				TryMove(nextDir);
			}
		}
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
		TileObject* monster = MapManager::GetEnemy(mIndex + direction);
		if (monster != nullptr && monster != this)
		{
			MoveFailed(direction);
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
			if (!success)
			{
				MoveFailed(direction);
			}
			return true;
		}
		return false;
	}
}