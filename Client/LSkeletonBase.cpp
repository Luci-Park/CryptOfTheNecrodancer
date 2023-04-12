#include "LSkeletonBase.h"
#include "LAudioClip.h"
#include "LResources.h"
#include "LObject.h"
#include "LSkeletonSprite.h"
#include "LMapManager.h"
namespace cl
{
	SkeletonBase::SkeletonBase(Scene* sc)
		: Monster(sc, true)
		, mbNoHead(false)
		, mbPause(true)
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
		GameCharacter::OnAttacked(attackPower);
		if (mHealth > 0 && mHealth <= 1 && !mbNoHead)
		{
			mSkelSprite->LostHead();
			PlayOnHeadLossSound();
			mbNoHead = true;
			mRunDir = mIndex - MapManager::GetPlayerIndex().Normalize();
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
				return MoveTowardsPlayer();
			}
		}
	}
	bool SkeletonBase::TryMove(Vector2 direction)
	{
		mbPause = !mbPause;
		if (direction != Vector2::Zero) mSprite->Jump();
		mMoveTarget += direction * UNITLENGTH;
		MapManager::Move(mIndex, mIndex + direction);
		mIndex += direction;
		mBefDir = direction;
		return true;
	}
	Vector2 SkeletonBase::MoveTowardsPlayer()
	{
		Vector2 dist = MapManager::GetPlayerIndex() - mIndex;
		if (dist.x > dist.y)
			return Vector2::Right * (signbit(dist.y) ? -1 : 1);
		else if (dist.x < dist.y)
			return Vector2::Down * (signbit(dist.x) ? -1 : 1);
		else
			return mBefDir;
	}
	Vector2 SkeletonBase::MoveAwayFromPlayer()
	{
		return mRunDir;
	}
}
