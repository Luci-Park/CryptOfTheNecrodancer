#include "LMonster.h"
#include "LCharacterSprite.h"
#include "LCadence.h"
#include "LMapManager.h"
#include "LWallTile.h"
#include "LMonsterWeapon.h"
#include "LMonsterHeart.h"
#include "LTileLight.h"
#include "LTime.h"
namespace cl
{
	Monster::Monster(Scene* sc, bool isTouchingGround)
		: GameCharacter(sc, isTouchingGround)
		, mDigPower(0)
		, mAttackPower(0)
		, mDrop(0)
		, mbIsActivated(false)
		, mbIsAggroed(false)
		, mPrevDir(Vector2::Zero)
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
		CheckAggro();
		CheckActivation();
		CheckShadow();
	}
	bool Monster::OnAttacked(float attackPower, Vector2 dir)
	{
		GameCharacter::OnAttacked(attackPower, dir);
		if (mHealth > 0)
		{
			mHeart->SetHearts(mMaxHealth, mHealth);
		}
		return true;
	}
	void Monster::OnDestroy()
	{
		//LeaveGold
		TileObject::OnDestroy();
	}
	void Monster::OnBeat()
	{
		if (mbIsActivated || mbIsAggroed)
		{
			mMoveSpeed = BeatManager::MoveSpeed() * 2 * Time::DeltaTime();
			mMoveState = MoveState::NotMoved;
			mSprite->Reset();
			mTransform->SetPos(mMoveTarget);
			mNextDir = Vector2::Zero;
			if (!UnSink())
			{
				Vector2 nextDir = GetNextDir();
				mSprite->Turn(nextDir);
				if (nextDir == Vector2::Zero) mMoveState = MoveState::Moved;
				else if (TryAttack(nextDir)) mMoveState = MoveState::Attacked;
				else if (TryDig(nextDir)) mMoveState = MoveState::Dug;
				else
					mNextDir = nextDir;
			}
			else
			{
				mMoveState = MoveState::Unsunked;
			}
		}
		else
		{
			mNextDir = Vector2::Zero;
			mMoveState = MoveState::Failed;
		}
	}
	void Monster::OnLateBeat()
	{
		if (mbIsActivated || mbIsAggroed)
		{
			TryMove();
			mSprite->Turn(mNextDir);
			mPrevDir = mNextDir;
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
			bool success = mDigPower > 0 ? wall->OnDig(mDigPower) : false;
			Recoil(direction);
			return true;
		}
		return false;
	}
	bool Monster::TryMove()
	{
		if (mMoveState != MoveState::NotMoved) return false;
		TileObject* object = MapManager::GetEnemy(mIndex + mNextDir);
		if (object != nullptr && object != this)
		{
			mMoveState = MoveState::IsAsking;
			if (!object->TryMove())
			{
				Recoil(mNextDir);
				mMoveState = MoveState::Failed;
				return false;
			}
		}
		mMoveState = MoveState::Moved;
		mMoveTarget += mNextDir * UNITLENGTH;
		if (abs(mNextDir.x) > 1 || abs(mNextDir.y) > 1)
		{
			int m = abs(mNextDir.y) > abs(mNextDir.x) ? mNextDir.y : mNextDir.x;
			mMoveSpeed = BeatManager::MoveSpeed() * 2 * Time::DeltaTime() * abs(m);
		}
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
	Vector2 Monster::CardinalMoveTowards()
	{
		Vector2 player = MapManager::GetPlayerIndex();
		if (player.x == mIndex.x || player.y == mIndex.y)
			return (player - mIndex).TileNormalize();
		Vector2 prevPlayer = player - MapManager::GetPlayer(player)->GetInput();
		if (Vector2::IsCardinal((prevPlayer - mIndex).TileNormalize()))
			return (prevPlayer - mIndex).TileNormalize();
		else
		{
			if (mPrevDir == Vector2::Zero)
			{
				if (abs(player.x - mIndex.x) >= abs(player.y - mIndex.y))
					return Vector2(player.x - mIndex.x, 0.0f).TileNormalize();
				else
					return Vector2(0.0f, player.y - mIndex.y).TileNormalize();
			}
		}
		return mPrevDir;
	}
	Vector2 Monster::DiagonalMoveTowards()
	{
		std::vector<Vector2> direction = {
			   {1, 0}, {0, 1}, {-1, 0}, {0, -1},
			   {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
		};
		std::vector<std::pair<float, int>> distances(direction.size());
		Vector2 playerPos = MapManager::GetPlayerIndex();
		for (int i = 0; i < direction.size(); ++i)
		{
			float distance = Vector2::Distance(mIndex + direction[i], playerPos);
			distances[i] = (std::make_pair(distance, i));
		}
		std::sort(distances.begin(), distances.end());
		for (auto it = distances.begin(); it != distances.end(); ++it)
		{
			Vector2 dest = mIndex + direction[it->second];
			if (dest == playerPos || (MapManager::GetEnemy(dest) == nullptr && MapManager::GetWall(dest) == nullptr))
				return direction[it->second];
		}
		return direction[distances.begin()->second];
	}
	Vector2 Monster::CardinalMoveAway()
	{
		std::vector<Vector2> direction = {
			   {1, 0}, {0, 1}, {-1, 0}, {0, -1}
		};
		std::vector<std::pair<float, int>> distances(direction.size());
		Vector2 playerPos = MapManager::GetPlayerIndex();
		for (int i = 0; i < direction.size(); ++i)
		{
			float distance = Vector2::Distance(mIndex + direction[i], playerPos);
			distances[i] = (std::make_pair(-distance, i));
		}
		std::sort(distances.begin(), distances.end());
		float mindistance = distances.begin()->first;
		for (auto it = distances.begin(); it != distances.end(); ++it)
		{
			if (it->second > mindistance)
				break;

			Vector2 dest = mIndex + direction[it->second];
			if (MapManager::IndexIsValid(dest)
				&& MapManager::GetEnemy(dest) == nullptr && MapManager::GetWall(dest) == nullptr)
				return direction[it->second];
		}
		return direction[distances.begin()->second];
	}
	Vector2 Monster::DiagonalMoveAway()
	{
		std::vector<Vector2> direction = {
			   {1, 1}, {1, -1}, {-1, 1}, {-1, -1},
			   {1, 0}, {0, 1}, {-1, 0}, {0, -1}
		};
		std::vector<std::pair<float, int>> distances(direction.size());
		Vector2 playerPos = MapManager::GetPlayerIndex();
		for (int i = 0; i < direction.size(); ++i)
		{
			float distance = Vector2::Distance(mIndex + direction[i], playerPos);
			distances[i] = (std::make_pair(-distance, i));
		}
		std::sort(distances.begin(), distances.end());
		for (auto it = distances.begin(); it != distances.end(); ++it)
		{
			Vector2 dest = mIndex + direction[it->second];
			if ((MapManager::GetEnemy(dest) == nullptr && MapManager::GetWall(dest) == nullptr))
				return direction[it->second];
		}
		return direction[distances.begin()->second];
	}
	void Monster::Trample()
	{
		int dy[4] = { 0, 1, 0, -1 };
		int dx[4] = { 1, 0, -1, 0 };
		for (int i = 0; i < 4; ++i)
		{
			Vector2 target = mIndex + Vector2(dx[i], dy[i]);
			WallTile* wall = MapManager::GetWall(target);
			TileObject* object = MapManager::GetEnemy(target);
			if (wall != nullptr) wall->OnDig(4);
			if (object != nullptr) object->OnAttacked(mMaxHealth, Vector2(dx[i], dy[i]));
		}
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
		Vector2 index = mTransform->GetPos() / UNITLENGTH;
		TileLight* light = MapManager::GetLight(index);
		if (light != nullptr)
		{
			if (!light->IsRevealed())
			{
				mSprite->SetActive(false);
				mHeart->SetActive(false);
			}
			else if (mbIsActivated || mbIsAggroed)
			{
				mSprite->SetActive(true);
				bool isInlight = light->IsInSight() && light->Illumination() > 0.5f;
				mSprite->SetShadow(!isInlight);
				mHeart->SetActive(true);
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