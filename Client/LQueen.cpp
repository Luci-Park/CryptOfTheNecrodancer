#include "LQueen.h"
#include "LQueenSprite.h"
#include "LMapManager.h"
namespace cl
{
	Queen::Queen(Scene* sc)
		:Monster(sc, false)
	{
		std::wstring path = L"..\\Assets\\Audio\\SoundEffects\\Enemies\\Boss\\DeepBlues\\";
		std::wstring extend = L".wav";
		std::wstring key = L"en_blues_queen_death_0";
		for (int i = 0; i < 3; ++i)
		{
			std::wstring nKey = key + std::to_wstring(i + 1);
			mDeathSounds[i] = Resources::Load<AudioClip>(nKey, path + nKey + extend);
		}
		key = L"en_blues_queen_sing_0";
		for (int i = 0; i < 6; ++i)
		{
			std::wstring nKey = key + std::to_wstring(i + 1);
			mSingSounds[i] = Resources::Load<AudioClip>(nKey, path + nKey + extend);
		}
	}
	void Queen::Initialize()
	{
		Monster::Initialize();
		mSprite = object::Instantiate<QueenSprite>(GameObject::GetScene(), mTransform, mTransform->GetPos(), eLayerType::Monster);
	}
	Vector2 Queen::GetNextDir()
	{
		return DiagonalMoveTowards();
	}
	void Queen::SetStats()
	{
		mAttackPower = 1.5f;
		mMaxHealth = 1;
	}
	void Queen::PlayOnAttackSound()
	{
		PlaySing();
	}
	void Queen::PlayOnHitSound()
	{
		PlaySing();
		Monster::PlayOnHitSound();
	}
	void Queen::PlayOnDeathSound()
	{
		int idx = GetRandomInt(0, 2);
		mDeathSounds[idx]->Play(false);
		Monster::PlayOnDeathSound();
	}
	void Queen::PlaySing()
	{
		int idx = GetRandomInt(0, 5);
		mSingSounds[idx]->Play(false);
	}
}