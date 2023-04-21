#include "LSkeletonBase.h"
#include "LSkeletonSprite.h"
#include "LMapManager.h"
namespace cl
{
	SkeletonBase::SkeletonBase(Scene* sc)
		: Monster(sc, true)
		, mbNoHead(false)
		, mbPause(false)
	{
		std::wstring path = L"..\\Assets\\Audio\\SoundEffects\\Enemies\\Monsters\\Skeleton\\";
		std::wstring extend = L".wav";

		mAttackSound = Resources::Load<AudioClip>(L"en_skel_attack_melee", path + L"en_skel_attack_melee" + extend);
		mDeathSound = Resources::Load<AudioClip>(L"en_skel_death", path + L"en_skel_death" + extend);
		
		std::wstring key = L"en_skel_head_loss_0";
		for (int i = 0; i < 3; ++i)
		{
			std::wstring nKey = key + std::to_wstring(i + 1);
			mHeadLossSound[i] = Resources::Load<AudioClip>(nKey, path + nKey + extend);
		}
		key = L"en_skel_hit_0";
		for (int i = 0; i < 3; ++i)
		{
			std::wstring nKey = key + std::to_wstring(i + 1);
			mHitSound[i] = Resources::Load<AudioClip>(nKey, path + nKey + extend);
		}
	}
	SkeletonBase::~SkeletonBase()
	{
	}
	void SkeletonBase::Initialize()
	{
		Monster::Initialize();
		mSkelSprite = object::Instantiate<SkeletonSprite>(GameObject::GetScene(), mTransform, mTransform->GetPos(), eLayerType::Monster);
		mSprite = mSkelSprite;
		mSkelSprite->SetSkeleY(GetY());
		mSkelSprite->Turn(CardinalMoveTowards());
		mSkelSprite->RaiseHand();
	}
	void SkeletonBase::Update()
	{
		Monster::Update();
			
	}
	void SkeletonBase::PlayOnAttackSound()
	{
		mAttackSound->SetVolume(voiceVol);
		mAttackSound->Play(false);
	}
	void SkeletonBase::PlayOnHitSound()
	{
		int idx = GetRandomInt(0, 2);  
		mHitSound[idx]->SetVolume(voiceVol);
		mHitSound[idx]->Play(false);
		Monster::PlayOnHitSound();
	}
	void SkeletonBase::PlayOnDeathSound()
	{
		mDeathSound->SetVolume(voiceVol);
		mDeathSound->Play(false);
		Monster::PlayOnDeathSound();
	}
	void SkeletonBase::OnLateBeat()
	{
		Monster::OnLateBeat();
		if(mMoveState != MoveState::Failed)
			mbPause = !mbPause;
	}
	void SkeletonBase::PlayOnHeadLossSound()
	{
		int idx = GetRandomInt(0, 2);
		mHeadLossSound[idx]->SetVolume(voiceVol);
		mHeadLossSound[idx]->Play(false);
		Monster::PlayOnHitSound();
	}
	void SkeletonBase::OnAttacked(float attackPower, Vector2 dir)
	{
		Monster::OnAttacked(attackPower, dir);
		if (mHealth > 0 && mHealth <= 1 && !mbNoHead)
		{
			mSkelSprite->LostHead();
			PlayOnHeadLossSound();
			mbNoHead = true;
			mPrevDir = dir;
		}
	}
	Vector2 SkeletonBase::GetNextDir()
	{
		if (mbNoHead)
		{
			return MoveAwayFromPlayer();
		}
		else {
			if (mbPause)
			{
				mSkelSprite->RaiseHand();
				return Vector2::Zero;
			}
			else
			{
				mSkelSprite->Idle();
				return CardinalMoveTowards();
			}
		}
	}
	Vector2 SkeletonBase::MoveAwayFromPlayer()
	{
		return mPrevDir;
	}
}
