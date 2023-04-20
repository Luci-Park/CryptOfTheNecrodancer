#include "LMinotaurBase.h"
namespace cl
{
	MinotaurBase::MinotaurBase(Scene* sc)
		:Monster(sc, true)
		, mBeatCount(0)
		, mMoveState(State::Idle)
	{
		mSize = 2;
		std::wstring path = L"..\\Assets\\Audio\\SoundEffects\\Enemies\\Midboss\\Minotaur\\";
		std::wstring extend = L".wav";
		mAttackSound = Resources::Load<AudioClip>(L"en_minotaur_attack", path + L"en_minotaur_attack" + extend);
		mDeathSound = Resources::Load<AudioClip>(L"en_minotaur_death", path + L"en_minotaur_death" + extend);
		mChargeSound = Resources::Load<AudioClip>(L"en_minotaur_charge", path + L"en_minotaur_charge" + extend);
		mWallImpactSound = Resources::Load<AudioClip>(L"en_minotaur_wallimpact", path + L"en_minotaur_wallimpact" + extend);
		mCrySound = Resources::Load<AudioClip>(L"en_minotaur_cry", path + L"en_minotaur_cry" + extend);
		std::wstring key = L"en_minotaur_hit_0";
		for (int i = 0; i < 4; ++i)
		{
			std::wstring newKey = key + std::to_wstring(i + 1);
			mHitSounds[i] = Resources::Load<AudioClip>(newKey, path + newKey + extend);
		}
	}
	MinotaurBase::~MinotaurBase()
	{
	}
	void MinotaurBase::Initialize()
	{
	}
	void MinotaurBase::OnAggroed()
	{
		mCrySound->Play(false);
	}
	void MinotaurBase::OnLateBeat()
	{
		Monster::OnLateBeat();
		mBeatCount++;
	}
	Vector2 MinotaurBase::GetNextDir()
	{
		if (mMoveState == State::Charge)
			mDigPower = 5;
		else
			mDigPower = 2;
		return Vector2();
	}
}
