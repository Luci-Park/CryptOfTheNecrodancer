#include "LKing.h"
#include "LKingSprite.h"
#include "LMapManager.h"
#include "LInput.h"
namespace cl
{
	King::King(Scene* sc)
		:Monster(sc, false)
		, mbStartAttack(false)
		, mAttackedDir(Vector2::Zero)
		, mBeatCount(0)
	{
		std::wstring path = L"..\\Assets\\Audio\\SoundEffects\\Enemies\\Boss\\DeepBlues\\";
		std::wstring extend = L".wav";
		mDeathSound = Resources::Load<AudioClip>(L"en_blues_king_death", path + L"en_blues_king_death" + extend);
		mCry = Resources::Load<AudioClip>(L"en_blues_king_cry", path + L"en_blues_king_cry" + extend);
		std::wstring key = L"en_blues_king_attack_0";
		for (int i = 0; i < 7; ++i)
		{
			std::wstring nKey = key + std::to_wstring(i + 1);
			mAttackSounds[i] = Resources::Load<AudioClip>(nKey, path + nKey + extend);
		}
		key = L"en_blues_king_hit_0";
		for (int i = 0; i < 4; ++i)
		{
			std::wstring nKey = key + std::to_wstring(i + 1);
			mHitSounds[i] = Resources::Load<AudioClip>(nKey, path + nKey + extend);
		}
		mLightSource = new LightSource(mTransform, 0.0, 10.0);
	}
	King::~King()
	{
		delete mLightSource;
		mLightSource = nullptr;
	}
	void King::Initialize()
	{	
		Monster::Initialize();
		mSprite = object::Instantiate<KingSprite>(GameObject::GetScene(), mTransform, mTransform->GetPos(), eLayerType::Monster);
		MapManager::SetKey(this);
	}
	void King::Update()
	{
		Monster::Update();
		if (Input::GetKeyDown(eKeyCode::Q))
			StartAttack();
	}
	bool King::OnAttacked(float attackPower, Vector2 dir)
	{
		mAttackedDir = dir;
		return Monster::OnAttacked(attackPower, dir);
	}
	void King::OnLateBeat()
	{
		Monster::OnLateBeat();
		if(mbIsActivated || mbIsAggroed)
			mBeatCount++;
		mAttackedDir = Vector2::Zero;
	}
	void King::StartAttack()
	{
		if (mbStartAttack == false)
		{
			mbStartAttack = true;
			mCry->Play(false);
		}
	}
	Vector2 King::GetNextDir()
	{
		if (mBeatCount >= 0)
		{
			if (!mbStartAttack)
			{
				if (mBeatCount % 2)
					return DiagonalMoveAway();
				return Vector2::Zero;
			}
			else {
				if (mAttackedDir != Vector2::Zero)
					return mAttackedDir;
				return DiagonalMoveTowards();
			}
		}
		return Vector2::Zero;
	}
	void King::SetStats()
	{
		mMaxHealth = 3;
		mAttackPower = 2;
	}
	void King::PlayOnAttackSound()
	{
		int idx = GetRandomInt(0, 6);
		mAttackSounds[idx]->Play(false);
		Monster::PlayOnHitSound();
	}
	void King::PlayOnHitSound()
	{
		int idx = GetRandomInt(0, 3);
		mHitSounds[idx]->Play(false);
	}
	void King::PlayOnDeathSound()
	{
		mDeathSound->Play(false);
	}
}