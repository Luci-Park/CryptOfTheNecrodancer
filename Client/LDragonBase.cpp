#include "LDragonBase.h"
#include "LMapManager.h"
namespace cl
{
	DragonBase::DragonBase(Scene* sc)
		:Monster(sc, true)
		, mBeatCount(0)
		, mDragonState(State::Idle)
	{
		mSize = 2;
		mLightSource = new LightSource(mTransform, 1.0, 1.0);
		std::wstring path = L"..\\Assets\\Audio\\SoundEffects\\Enemies\\Midboss\\Dragon\\";
		std::wstring extend = L".wav";
		mAttackSound = Resources::Load<AudioClip>(L"en_dragon_attack_melee", path + L"en_dragon_attack_melee" + extend);
		mDeathSound = Resources::Load<AudioClip>(L"en_dragon_death", path + L"en_dragon_death" + extend);
		mCrySound = Resources::Load<AudioClip>(L"en_dragon_cry", path + L"en_dragon_cry" + extend);
		mPrefireSound = Resources::Load<AudioClip>(L"en_dragon_attack_prefire", path + L"en_dragon_attack_prefire" + extend);
		mFireSound = Resources::Load<AudioClip>(L"en_dragon_attack_fire", path + L"en_dragon_attack_fire" + extend);
		std::wstring key = L"en_dragon_hit_0";
		for (int i = 0; i < 3; ++i)
		{
			std::wstring newKey = key + std::to_wstring(i + 1);
			mHitSounds[i] = Resources::Load<AudioClip>(newKey, path + newKey + extend);
		}
		key = L"en_dragon_walk_0";
		for (int i = 0; i < 3; ++i)
		{
			std::wstring newKey = key + std::to_wstring(i + 1);
			mWalkSounds[i] = Resources::Load<AudioClip>(newKey, path + newKey + extend);
		}
	}
	DragonBase::~DragonBase()
	{
		delete mLightSource;
		mLightSource = nullptr;
	}
	void DragonBase::Initialize()
	{
		Monster::Initialize();
	}
	void DragonBase::OnAggroed()
	{
		mCrySound->Play(false);
	}
	void DragonBase::OnLateBeat()
	{
		Monster::OnLateBeat();
		if (mMoveState == MoveState::Failed || mMoveState == MoveState::Dug)
		{
			Trample();
			mBeatCount = 0;
		}
		else
		{
			mBeatCount++;
		}
		if (mMoveState == MoveState::Moved && mNextDir != Vector2::Zero)
			PlayWalkSound();
	}
	void DragonBase::PlayOnAttackSound()
	{
		mAttackSound->Play(false);
	}
	void DragonBase::PlayOnHitSound()
	{
		int idx = GetRandomInt(0, 2);
		mHitSounds[idx]->Play(false);
		Monster::PlayOnHitSound();
	}
	void DragonBase::PlayOnDeathSound()
	{
		mDeathSound->Play(false);
		Monster::PlayOnDeathSound();
	}
	Vector2 DragonBase::GetNextDir()
	{
		if (mBeatCount % 2)
			return CardinalMoveTowards();
		else
			return Vector2::Zero;
	}
	void DragonBase::PlayWalkSound()
	{
		int idx = GetRandomInt(0, 2);
		mWalkSounds[idx]->Play(false);
	}
	void DragonBase::SetDragonState(State state)
	{
		if (mDragonState != state)
		{
			mDragonState = state;
			mBeatCount = 0;
			if (state == State::ReadyFire)
				mPrefireSound->Play(false);
			else if (state == State::Fire)
				mFireSound->Play(false);
				
		}
	}
}
