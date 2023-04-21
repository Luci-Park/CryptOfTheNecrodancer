#include "LBatBase.h"
#include "LMapManager.h"
namespace cl
{
	BatBase::BatBase(Scene* sc)
		:Monster(sc, false)
	{
		std::wstring path = L"..\\Assets\\Audio\\SoundEffects\\Enemies\\Monsters\\Bat\\";
		std::wstring extend = L".wav";

		mAttackSound = Resources::Load<AudioClip>(L"en_bat_attack", path + L"en_bat_attack" + extend);
		mHitSound = Resources::Load<AudioClip>(L"en_bat_hit", path + L"en_bat_hit" + extend);
		mDeathSound = Resources::Load<AudioClip>(L"en_bat_death", path + L"en_bat_death" + extend);
	}
	BatBase::~BatBase()
	{
	}

	void BatBase::PlayOnAttackSound()
	{
		mAttackSound->Play(false);
	}
	void BatBase::PlayOnHitSound()
	{
		mHitSound->Play(false);
		Monster::PlayOnHitSound();
	}
	void BatBase::PlayOnDeathSound()
	{
		mDeathSound->Play(false);
		Monster::PlayOnDeathSound();
	}
	Vector2 BatBase::GetNextDir()
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
		if (possible.size() == 0)
		{
			mMoveState = MoveState::Failed;
			return Vector2::Zero;
		}
		Vector2 dir;
		int idx = GetRandomInt(0, possible.size() - 1);
		return Vector2(dx[possible[idx]], dy[possible[idx]]);
	}
}