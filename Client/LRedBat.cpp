#include "LRedBat.h"
#include "LResources.h"
#include "LAudioClip.h"
#include "LMapManager.h"
#include "LRedBatSprite.h"
#include "LObject.h"
namespace cl
{
	RedBat::RedBat(Scene* sc)
		:Monster(sc, false)
	{
		std::wstring path = L"..\\Assets\\Audio\\SoundEffects\\Enemies\\Monsters\\Bat\\";
		std::wstring extend = L".wav";

		mAttackSound = Resources::Load<AudioClip>(L"en_bat_attack", path + L"en_bat_attack" + extend);
		mHitSound = Resources::Load<AudioClip>(L"en_bat_hit", path + L"en_bat_hit" + extend);
		mDeathSound = Resources::Load<AudioClip>(L"en_bat_death", path + L"en_bat_death" + extend);
	}
	RedBat::~RedBat()
	{
	}
	void RedBat::Initialize()
	{
		Monster::Initialize();
		mSprite = object::Instantiate<RedBatSprite>(GameObject::GetScene(), mTransform, mTransform->GetPos(), eLayerType::Monster);
	}
	void RedBat::PlayOnAttackSound()
	{
		mAttackSound->SetVolume(voiceVol);
		mAttackSound->Play(false);
	}
	void RedBat::PlayOnHitSound()
	{
		mHitSound->SetVolume(voiceVol);
		mHitSound->Play(false);
	}
	void RedBat::PlayOnDeathSound()
	{
		mDeathSound->SetVolume(voiceVol);
		mDeathSound->Play(false);
	}
	void RedBat::SetStats()
	{
		mMaxHealth = 1;
		mAttackPower = 1.0f;
		mDrop = 3;
	}
	Vector2 RedBat::GetNextDir()
	{
		int dx[4] = { 0, 1, 0, -1 };
		int dy[4] = { 1, 0, -1, 0 };
		std::vector<int>possible;
		for (int i = 0; i < 4; i++)
		{
			if (MapManager::GetTileObject(mIndex + Vector2(dx[i], dy[i])) == nullptr
				&& MapManager::GetWall(mIndex + Vector2(dx[i], dy[i])) == nullptr)
				possible.push_back(i);
		}
		if (possible.size() == 0) return Vector2::Zero;
		Vector2 dir;
		int idx = GetRandomInt(0, possible.size() - 1);
		return Vector2(dx[possible[idx]], dy[possible[idx]]);
	}
}