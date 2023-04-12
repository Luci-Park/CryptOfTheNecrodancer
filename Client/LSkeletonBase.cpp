#include "LSkeletonBase.h"
#include "LAudioClip.h"
#include "LResources.h"
#include "LObject.h"
#include "LSkeletonSprite.h"
#include "LMapManager.h"
#include "LCadence.h"
namespace cl
{
	SkeletonBase::SkeletonBase(Scene* sc)
		: Monster(sc, true)
		, mbNoHead(false)
		, mbPause(true)
		, mMoveDir(Vector2::Left)
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
	}
	void SkeletonBase::Update()
	{
		Monster::Update();
		if(!mbNoHead)
			mMoveDir = MoveTowardsPlayer();
			
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
	void SkeletonBase::PlayOnHeadLossSound()
	{
		int idx = GetRandomInt(0, 2);
		mHeadLossSound[idx]->SetVolume(voiceVol);
		mHeadLossSound[idx]->Play(false);
		Monster::PlayOnHitSound();
	}
	void SkeletonBase::OnAttacked(float attackPower)
	{
		Monster::OnAttacked(attackPower);
		if (mHealth > 0 && mHealth <= 1 && !mbNoHead)
		{
			mSkelSprite->LostHead();
			PlayOnHeadLossSound();
			mbNoHead = true;
			mRunDir = MapManager::GetPlayer(MapManager::GetPlayerIndex())->GetInput();
		}
	}
	Vector2 SkeletonBase::GetNextDir()
	{
		if (mbNoHead)
		{
			return MoveAwayFromPlayer();
		}
		else {
			mMoveDir = MoveTowardsPlayer();
			if (mbPause)
			{
				mSkelSprite->RaiseHand();
				return Vector2::Zero;
			}
			else
			{
				mSkelSprite->Idle();
				return mMoveDir;
			}
		}
	}
	bool SkeletonBase::TryMove(Vector2 direction)
	{
		mbPause = !mbPause;
		if (direction != Vector2::Zero)
		{
			mSprite->Jump();
			mMoveDir = direction;
		}
		mMoveTarget += direction * UNITLENGTH;
		MapManager::Move(mIndex, mIndex + direction);
		mIndex += direction;
		return true;
	}
	Vector2 SkeletonBase::MoveTowardsPlayer()
	{
		Vector2 player = MapManager::GetPlayerIndex();
		if (player.x == mIndex.x || player.y == mIndex.y)
			return (player - mIndex).Normalize();
		else
			return mMoveDir;
	}
	Vector2 SkeletonBase::MoveAwayFromPlayer()
	{
		return mRunDir;
	}
}
