#include "LCadence.h"
#include "LCadenceSound.h"
#include "LCadenceSprite.h"
#include "LLightSource.h"
#include "LCadenceShovelEffect.h"
#include "LHealth.h"
#include "LMapManager.h"
#include "LBeatManager.h"
#include "LGrooveChain.h"
#include "LObject.h"
#include "LCamera.h"
#include "LInput.h"
#include "LTime.h"
#include "LWallTile.h"
#include "LShovel.h"
#include "LDagger.h"
#include "LWeapon.h"
#include "LItem.h"
namespace cl
{
	Cadence::Cadence(Scene* scene)
		: GameCharacter(scene, true)
		, consecutiveHits(0)
		, mMoved(false)
	{
		Camera::SetTarget(this);
		mHealth = new Health(this);
		mLightSource = new LightSource(mTransform, 1.25, 3);
	}
	Cadence::~Cadence()
	{
		if (mSound != nullptr)
		{
			delete mSound; 
			mSound = nullptr;
		}
		if (mLightSource != nullptr)
		{
			delete mLightSource;
			mLightSource = nullptr;
		}
		if (mHealth != nullptr)
		{
			delete mHealth;
			mHealth = nullptr;
		}
		Camera::SetTarget(nullptr);
	}
	void Cadence::Initialize()
	{
		GameCharacter::Initialize();
		mTransform->SetScale(Vector2::One * UNITSCALE);
		mSound = new CadenceSound();

		mSprite = object::Instantiate<CadenceSprite>(GameObject::GetScene(), GameObject::mTransform, GameObject::mTransform->GetPos(), eLayerType::Player);
		mItems[(int)eItemTypes::Weapon] = object::Instantiate<Dagger>(GameObject::GetScene(), GameObject::mTransform, GameObject::mTransform->GetPos(), eLayerType::Items);
		mItems[(int)eItemTypes::Tool] = object::Instantiate<Shovel>(GameObject::GetScene(), GameObject::mTransform, GameObject::mTransform->GetPos(), eLayerType::Items);
		
		mShovelEffect = object::Instantiate<CadenceShovelEffect>(GameObject::GetScene(), GameObject::mTransform, GameObject::mTransform->GetPos(), eLayerType::Effects);
		BeatManager::AddCharacters(this);
	}
	void Cadence::Update()
	{
		mMoveSpeed = BeatManager::MoveSpeed() * 2 * Time::DeltaTime();
		mTransform->SetPos(Vector2::MoveTowards(mTransform->GetPos(), mMoveTarget, mMoveSpeed));
		if (Vector2::Distance(mTransform->GetPos(), mMoveTarget) <= 0.01f)
		{
			if (mbIsMoving)
			{
				mbIsMoving = false;
				mSprite->Reset();
				if (mbIsTouchingGround)
					MapManager::OnTileStep(this, mIndex);
				Item* item = MapManager::GetItem(mIndex);
				if (item != nullptr) item->PickUpItem(this);
			}
			else
			{
				SetInput();
				if (mInput != Vector2::One)
				{
					SetSprite();
					if (!UnSink())
						OnMove(mInput);
					BeatManager::OnPlayerMove();
				}
			}
		}
		else {
			mbIsMoving = true;
		}
		TileObject::Update();
		if (Input::GetKeyDown(eKeyCode::O))
			BeatManager::OnPlayerMove();
	}
	void Cadence::Render(HDC hdc)
	{
		GameCharacter::Render(hdc);
	}

	bool Cadence::OnAttacked(float attackPower, Vector2 dir)
	{
		mHealth->OnDamage(attackPower);
		if (mHealth->CurrentHealth() > 0)
		{
			Camera::StartShake();
			PlayOnHitSound();
			GrooveChainManager::LooseGroove();
			//mSprite->Flash
		}
		return true;
	}
	bool Cadence::TryMove()
	{
		if (mMoved)
			return false;
		Vector2 dest = mIndex + mInput;
		MapManager::PlayerMove(this, mIndex, dest);
		mSprite->Jump();
		mIndex = dest;
		mMoveTarget += mInput * UNITLENGTH;
		mMoved = true;
		return true;
	}
	void Cadence::OnDestroy()
	{
		PlayOnDeathSound();
	}

	void Cadence::OnBeat()
	{
	}
	void Cadence::OnLateBeat()
	{
	}
	void Cadence::OnBeatChanged()
	{
		GameCharacter::OnBeatChanged();
	}

	void Cadence::SwitchItem(Item* item, eItemTypes type)
	{
		int idx = (int)type;
		if (mItems[idx] != nullptr)
		{
			mItems[idx]->SetItem(MapManager::SetItem(mItems[idx], mIndex));
		
		}
		mItems[idx] = item;
	}

	void Cadence::OnMove(Vector2 direction)
	{
		if (TryAttack(direction))
		{
			consecutiveHits++;
		}
		else {
			consecutiveHits = 0;
			if (!TryDig(direction))
				TryMove();
		}
		mMoved = true;
	}

	bool Cadence::TryAttack(Vector2 direction)
	{
		if (mWeapon() == nullptr)
		{
			GrooveChainManager::LooseGroove();
			return false;
		}
		bool didAttack = mWeapon()->Attack(mIndex, direction);
		if (didAttack)
		{
			PlayOnAttackSound();
			Camera::StartShake();
			if (MapManager::GetEnemy(mIndex + direction) == nullptr)
			{
				GrooveChainManager::IncreaseKillCount();
				//Items killcount here
			}
		}
		return didAttack;
	}

	bool Cadence::TryDig(Vector2 direction)
	{
		WallTile* wall = MapManager::GetWall(mIndex + direction);
		if (wall)
		{
			if (mShovel() != nullptr)
			{
				mShovelEffect->OnDig(wall, mShovel()->GetSprite());
				bool success = mShovel()->Dig(wall);
				if (success)
				{
					mSound->PlayOnDigSound();
					Camera::StartShake();
				}
				else
				{
					GrooveChainManager::LooseGroove();
				}
			}
			return true;//I tried dig
		}
		return false;
	}

	void Cadence::SetInput()
	{
		mMoved = false;
		mInput = Vector2::One;
		if (Input::GetKeyDown(eKeyCode::A))
		{
			mInput = Vector2::Left;
		}

		if (Input::GetKeyDown(eKeyCode::D))
		{
			mInput = Vector2::Right;
		}

		if (Input::GetKeyDown(eKeyCode::W))
		{
			mInput = Vector2::Up;
		}

		if (Input::GetKeyDown(eKeyCode::S))
		{
			mInput = Vector2::Down;
		}
	}

	void Cadence::SetSprite()
	{
		if (mInput != Vector2::One)
		{
			mShovelEffect->Reset();
			mSprite->Turn(mInput);
		}
	}

	void Cadence::PlayOnAttackSound()
	{
		if (mWeapon()->isMelee())
		{
			mSound->PlayMeleeSound(consecutiveHits);
		}
		else
		{
			mSound->PlayRangedSound();
		}
	}

	void Cadence::PlayOnHitSound()
	{
		mSound->PlayOnHitSound();
	}

	void Cadence::PlayOnDeathSound()
	{
		mSound->PlayOnDeathSound();
	}
}