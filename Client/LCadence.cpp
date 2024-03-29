#include "LCadence.h"
#include "LCadenceSound.h"
#include "LCadenceSprite.h"
#include "LLightSource.h"
#include "LCadenceShovelEffect.h"
#include "LBeatJudge.h"
#include "LHealth.h"
#include "LMapManager.h"
#include "LConductor.h"
#include "LGrooveChain.h"
#include "LSceneManager.h"
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
	void Cadence::Reset()
	{
		Health::Reset();
	}
	Cadence::Cadence(Scene* scene)
		: GameCharacter(scene, true)
		, consecutiveHits(0)
		, mMoved(false)
		, mInput(Vector2::Zero)
		, mJudge(nullptr)
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
		if(SceneManager::GetActiveScene()->GetSceneType() != eSceneType::Lobby)
			mJudge = object::Instantiate<BeatJudge>(eLayerType::System);
		mPrevPos = mIndex;
	}
	void Cadence::Update()
	{
		Vector2 input = CheckInput();
		if (Vector2::IsCardinal(input))
		{
			if (mJudge == nullptr || mJudge->IsInBeat())
			{
				if (mJudge != nullptr) 
					mJudge->OnValidInput();

				mTransform->SetPos(mMoveTarget);

				if (mbIsMoving)
					OnDestReached();

				mInput = input;
				SetSprite();
				if (!UnSink())
				{
					mPrevPos = mIndex;
					OnMove(mInput);
				}
				Conductor::Instance().OnPlayerMove();
				return;
			}
			else
			{
				GrooveChainManager::Instance().LooseGroove();
			}
		}
		mMoveSpeed = Conductor::Instance().MoveSpeed() * 2 * Time::DeltaTime();
		mTransform->SetPos(Vector2::MoveTowards(mTransform->GetPos(), mMoveTarget, mMoveSpeed));
		if (Vector2::Distance(mTransform->GetPos(), mMoveTarget) <= 0.01f)
		{
			if (mbIsMoving)
			{
				OnDestReached();
			}
		}
		else {
			mbIsMoving = true;
		}
		TileObject::Update();
		if (Input::GetKeyDown(eKeyCode::O))
		{
			Heal(10);
		}
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
			GrooveChainManager::Instance().LooseGroove();
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
		SceneManager::LoadScene(eSceneType::Lobby);
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

	void Cadence::Heal(int amount)
	{
		mHealth->OnHeal(amount);
		mSound->PlayHealSound();
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

	void Cadence::OnDestReached()
	{
		mbIsMoving = false;
		mSprite->Reset();
		if (mbIsTouchingGround)
			MapManager::OnTileStep(this, mIndex);
		Item* item = MapManager::GetItem(mIndex);
		if (item != nullptr) item->PickUpItem(this);
	}

	void Cadence::PlayVictory()
	{
		mSound->PlayVictorySound();
	}

	bool Cadence::TryAttack(Vector2 direction)
	{
		if (mWeapon() == nullptr)
		{
			GrooveChainManager::Instance().LooseGroove();
			return false;
		}
		bool didAttack = mWeapon()->Attack(mIndex, direction);
		if (didAttack)
		{
			PlayOnAttackSound();
			Camera::StartShake();
			if (MapManager::GetEnemy(mIndex + direction) == nullptr)
			{
				GrooveChainManager::Instance().IncreaseKillCount();
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
					GrooveChainManager::Instance().LooseGroove();
				}
			}
			return true;//I tried dig
		}
		return false;
	}

	Vector2 Cadence::CheckInput()
	{
		mMoved = false;
		Vector2 input = Vector2::Zero;
		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			input = Vector2::Left;
		}

		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			input = Vector2::Right;
		}

		if (Input::GetKeyDown(eKeyCode::UP))
		{
			input = Vector2::Up;
		}

		if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			input = Vector2::Down;
		}
		return input;
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