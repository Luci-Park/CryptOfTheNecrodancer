#include "LCadence.h"
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
#include "LResources.h"
#include "LAudioClip.h"
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
		SetAudioClip();
		mMaxHealth = 3;
		mHealth = 3;
	}
	Cadence::~Cadence()
	{
		delete mShovel; mShovel = nullptr;
		Camera::SetTarget(nullptr);
	}
	void Cadence::Initialize()
	{
		GameCharacter::Initialize();
		mTransform->SetScale(Vector2::One * UNITSCALE);

		//mSpriteRenderer = AddComponent<SpriteRenderer>();
		//mSpriteRenderer->SetImage(L"shadow", L"..\\Assets\\Arts\\Player\\Player_Shadow.bmp");
		//mSpriteRenderer->AddAlpha(100);

		mSprite = object::Instantiate<CadenceSprite>(GameObject::GetScene(), GameObject::mTransform, GameObject::mTransform->GetPos(), eLayerType::Player);
		mWeapon = object::Instantiate<Dagger>(GameObject::GetScene(), GameObject::mTransform, GameObject::mTransform->GetPos(), eLayerType::Effects);
		mShovelEffect = object::Instantiate<CadenceShovelEffect>(GameObject::GetScene(), GameObject::mTransform, GameObject::mTransform->GetPos(), eLayerType::Effects);
	}
	void Cadence::Update()
	{
		GameCharacter::Update();
		if (!mbIsMoving)
		{
			GetInput();
			if (mInput != Vector2::One)
			{
				SetSprite();
				if (!UnSink())
					OnMove(mInput);
				BeatManager::OnPlayerMove();
			}
		}
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
		mWeapon->OnBeatChanged();
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
			if (consecutiveHits >= mMeleeHitVoice.size())
				consecutiveHits = mMeleeHitVoice.size() - 1;
		}
		else {
			consecutiveHits = 0;
			if (!TryDig(direction))
				TryMove(direction);
		}
	}

	bool Cadence::TryAttack(Vector2 direction)
	{
		bool didAttack = mWeapon->Attack(mIndex, direction);
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
					PlayOnDigSound();
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

	void Cadence::GetInput()
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

	void Cadence::SetAudioClip()
	{
		SetDigSound();
		SetAttackSound();
		SetDeathSound();
		SetOnHitSound();
		mDeathSFX = Resources::Load<AudioClip>(L"PlayerHit", L"..\\Assets\\Audio\\SoundEffects\\SFX\\sfx_player_death_ST.wav");
		mHitSFX = Resources::Load<AudioClip>(L"PlayerHit", L"..\\Assets\\Audio\\SoundEffects\\SFX\\sfx_player_hit_ST.wav");

	}
	void Cadence::PlayOnDigSound()
	{
		int random = GetRandomInt(0, mDigVoice.size());
		mDigVoice[random]->SetVolume(25.f);
		mDigVoice[random]->Play(false);
	}

	void Cadence::PlayOnAttackSound()
	{
		if (mWeapon->isMelee())
		{
			int random = GetRandomInt(0, mMeleeHitVoice[0].size() - 1);
			mMeleeHitVoice[consecutiveHits][random]->Play(false);
		}
		else
		{
			int random = GetRandomInt(0, mRangedHitVoice.size() - 1);
			mRangedHitVoice[random]->Play(false);
		}
	}

	void Cadence::PlayOnHitSound()
	{
		mHitSFX->Play(false);
		int random = GetRandomInt(0, mOnAttackedVoice.size() - 1);
		mOnAttackedVoice[random]->Play(false);
	}

	void Cadence::PlayOnDeathSound()
	{
		mDeathSFX->Play(false);
		int random = GetRandomInt(0, mDeathVoice.size() - 1);
		mDeathVoice[random]->Play(false);
	}
	void Cadence::SetDigSound()
	{
		mDigVoice.resize(6);
		std::wstring cad = L"vo_cad_";
		std::wstring key = cad + L"dig_0";
		std::wstring path = L"..\\Assets\\Audio\\SoundEffects\\CadenceVoice\\";

		for (int i = 0; i < mDigVoice.size(); ++i)
		{
			std::wstring newKey = key + std::to_wstring(i + 1);
			std::wstring newPath = path + newKey + L".wav";
			mDigVoice[i] = Resources::Load<AudioClip>(newKey, newPath);
		}
	}
	void Cadence::SetAttackSound()
	{
		mMeleeHitVoice.resize(4);
		std::wstring cad = L"vo_cad_";
		std::wstring key = cad + L"melee_";
		std::wstring path = L"..\\Assets\\Audio\\SoundEffects\\CadenceVoice\\";
		for (int i = 0; i < mMeleeHitVoice.size(); ++i)
		{
			mMeleeHitVoice[i].resize(4);
			std::wstring number = std::to_wstring(i + 1) + L"_0";
			for (int j = 0; j < mMeleeHitVoice[i].size(); j++)
			{
				std::wstring newKey = key + number + std::to_wstring(j + 1);
				std::wstring newPath = path + newKey + L".wav";
				mMeleeHitVoice[i][j] = Resources::Load<AudioClip>(newKey, newPath);
			}
		}

		mRangedHitVoice.resize(7);
		key = cad + L"ranged_0";
		for (int i = 0; i < mRangedHitVoice.size(); ++i)
		{
			std::wstring newKey = key + std::to_wstring(i + 1);
			std::wstring newPath = path + newKey + L".wav";
			mRangedHitVoice[i] = Resources::Load<AudioClip>(newKey, newPath);
		}
	}
	void Cadence::SetDeathSound()
	{
		mDeathVoice.resize(3);
		std::wstring cad = L"vo_cad_";
		std::wstring key = cad + L"death_0";
		std::wstring path = L"..\\Assets\\Audio\\SoundEffects\\CadenceVoice\\";

		for (int i = 0; i < mDeathVoice.size(); ++i)
		{
			std::wstring newKey = key + std::to_wstring(i + 1);
			std::wstring newPath = path + newKey + L".wav";
			mDeathVoice[i] = Resources::Load<AudioClip>(newKey, newPath);
		}
	}
	void Cadence::SetOnHitSound()
	{
		mOnAttackedVoice.resize(3);
		std::wstring cad = L"vo_cad_";
		std::wstring key = cad + L"hurt_0";
		std::wstring path = L"..\\Assets\\Audio\\SoundEffects\\CadenceVoice\\";

		for (int i = 0; i < mOnAttackedVoice.size(); ++i)
		{
			std::wstring newKey = key + std::to_wstring(i + 1);
			std::wstring newPath = path + newKey + L".wav";
			mOnAttackedVoice[i] = Resources::Load<AudioClip>(newKey, newPath);
		}
	}
}