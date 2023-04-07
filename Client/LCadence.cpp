#include "LCadence.h"
#include "LCadenceSound.h"
#include "LCadenceSprite.h"
#include "LCadenceShovelEffect.h"
#include "LMapManager.h"
#include "LBeatManager.h"
#include "LObject.h"
#include "LCamera.h"
#include "LInput.h"
#include "LTime.h"
#include "LSpriteRenderer.h"
#include "LWallTile.h"
#include "LShovel.h"
#include "LDagger.h"
#include "LWeapon.h"
#include "LItem.h"
namespace cl
{
	Cadence::Cadence(Scene* scene)
		: GameCharacter(scene, true)
		, mSpriteRenderer(nullptr)
		, consecutiveHits(0)
	{
		//Camera::SetTarget(this);
		mShovel = new Shovel();
		mMaxHealth = 3;
		mHealth = 3;
	}
	Cadence::~Cadence()
	{
		delete mShovel; mShovel = nullptr;
		delete mSound; 
		mSound = nullptr;
		Camera::SetTarget(nullptr);
	}
	void Cadence::Initialize()
	{
		GameCharacter::Initialize();
		mTransform->SetScale(Vector2::One * UNITSCALE);
		mSound = new CadenceSound();
		mSprite = object::Instantiate<CadenceSprite>(GameObject::GetScene(), GameObject::mTransform, GameObject::mTransform->GetPos(), eLayerType::Player);
		mItems[(int)eItemTypes::Weapon] = object::Instantiate<Dagger>(GameObject::GetScene(), GameObject::mTransform, GameObject::mTransform->GetPos(), eLayerType::Effects);
		mShovelEffect = object::Instantiate<CadenceShovelEffect>(GameObject::GetScene(), GameObject::mTransform, GameObject::mTransform->GetPos(), eLayerType::Effects);

	}
	void Cadence::Update()
	{
		mTransform->SetPos(Vector2::MoveTowards(mTransform->GetPos(), mMoveTarget, BeatManager::MoveSpeed() * 2 * Time::DeltaTime()));
		if (Vector2::Distance(mTransform->GetPos(), mMoveTarget) <= 0.01f)
		{
			if (mbIsMoving)
			{
				mbIsMoving = false;
				mSprite->Reset();
				if (mbIsTouchingGround)
					MapManager::OnTileStep(this, mIndex);
				Item* item = MapManager::GetItem(mIndex);
				if (item) item->PickUpItem(this);
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

	void Cadence::OnAttacked(float attackPower)
	{
		mHealth -= attackPower;
		if (mHealth > 0)
		{
			Camera::StartShake();
			PlayOnHitSound();
			//mSprite->Flash
		}
		else
		{
			PlayOnDeathSound();
			OnDestroy();
		}
	}
	void Cadence::OnDestroy()
	{
	}

	void Cadence::OnBeat()
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
			MapManager::SetItem(mItems[idx], mIndex);
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
				TryMove(direction);
		}
	}

	bool Cadence::TryAttack(Vector2 direction)
	{
		bool didAttack = mItems[(int)eItemTypes::Weapon]->Use(this);
		if (didAttack)
			PlayOnAttackSound();
		return didAttack;
	}

	bool Cadence::TryDig(Vector2 direction)
	{
		WallTile* wall = MapManager::GetWall(mIndex + direction);
		if (wall)
		{
			if (mShovel)
			{
				mShovelEffect->OnDig(wall, mShovel);
				bool success = mShovel->Dig(wall);
				if (success)
				{
					mSound->PlayOnDigSound();
					Camera::StartShake();
				}
			}
			return true;//I tried dig
		}
		return false;
	}
	bool Cadence::TryMove(Vector2 direction)
	{
		Vector2 dest = mIndex + direction;
		MapManager::PlayerMove(mIndex, dest);
		mSprite->Jump();
		mIndex = dest;
		mMoveTarget += direction * UNITLENGTH;
		return true;
	}

	void Cadence::SetInput()
	{
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
		Weapon* weapon = (Weapon*)mItems[(int)eItemTypes::Weapon];
		if (weapon->isMelee())
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