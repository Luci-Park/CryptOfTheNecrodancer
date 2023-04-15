#include "LKing.h"
#include "LAudioClip.h"
#include "LResources.h"
#include "LObject.h"
#include "LKingSprite.h"
#include "LMapManager.h"
namespace cl
{
	King::King(Scene* sc)
		:Monster(sc, false)
		, mbStartAttack(false)
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
	}
	void King::Initialize()
	{
		Monster::Initialize();
		mKingSprite = object::Instantiate<KingSprite>(GameObject::GetScene(), mTransform, mTransform->GetPos(), eLayerType::Monster);
		mSprite = mKingSprite;
	}
	void King::StartAttack()
	{
		if (mbStartAttack = false)
		{
			mbStartAttack = true;
			mCry->Play(false);
		}
	}
	Vector2 King::GetNextDir()
	{
		if (!mbStartAttack)
			return MoveAwayPlayer();
		return MoveTowardsPlayer();
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
	Vector2 King::MoveAwayPlayer()
	{
		Vector2 player = MapManager::GetPlayerIndex();
		Vector2 dir = (mIndex - player).Normalize();
		return dir;
	}
	Vector2 King::MoveTowardsPlayer()
	{
		Vector2 player = MapManager::GetPlayerIndex();
		Vector2 dir = (player - mIndex).Normalize();
		return dir;
	}
}