#include "LMonster.h"
#include "LCharacterSprite.h"
#include "LCadence.h"
#include "LMapManager.h"
#include "LWallTile.h"
#include "LObject.h"
#include "LMonsterWeapon.h"
namespace cl
{
	Monster::Monster(Scene* sc, bool isTouchingGround)
		: GameCharacter(sc, isTouchingGround)
	{
	}
	Monster::~Monster()
	{
	}
	void Monster::Initialize()
	{
		GameCharacter::Initialize();
		SetStats();
		SetWeapon();
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
	void Monster::OnDestroy()
	{
		MapManager::DestroyTileObject(mIndex);
		//LeaveGold
	}
	void Monster::OnBeat()
	{
		mSprite->Reset();
		if (!UnSink())
		{
			Vector2 nextDir = GetNextDir();
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
			//Effect;
			return true;
		}
		if(MapManager::GetEnemy(mIndex + direction))
			return true;
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
				//MoveFailed;
			}
			return true;
		}
		return false;
	}
}