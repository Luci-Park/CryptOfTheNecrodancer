#include "LBat.h"
#include "LResources.h"
#include "LAudioClip.h"
#include "LMapManager.h"
#include "LBatSprite.h"
#include "LObject.h"
namespace cl
{
	Bat::Bat(Scene* sc)
		:Monster(sc, false)
		, mbMove(true)
	{
		std::wstring path = L"..\\Assets\\Audio\\SoundEffects\\Enemies\\Monsters\\Bat\\";
		std::wstring extend = L".wav";

		mAttackSound = Resources::Load<AudioClip>(L"en_bat_attack", path + L"en_bat_attack" + extend);
		mHitSound = Resources::Load<AudioClip>(L"en_bat_hit", path + L"en_bat_hit" + extend);
		mDeathSound = Resources::Load<AudioClip>(L"en_bat_death", path + L"en_bat_death" + extend);
	}
	Bat::~Bat()
	{
	}
	void Bat::Initialize()
	{
		Monster::Initialize();
		mSprite = object::Instantiate<BatSprite>(GameObject::GetScene(), mTransform, mTransform->GetPos(), eLayerType::Monster);
	}
	void Bat::PlayOnAttackSound()
	{
		mAttackSound->SetVolume(voiceVol);
		mAttackSound->Play(false);
	}
	void Bat::PlayOnHitSound()
	{
		mHitSound->SetVolume(voiceVol);
		mHitSound->Play(false);
		Monster::PlayOnHitSound();
	}
	void Bat::PlayOnDeathSound()
	{
		mDeathSound->SetVolume(voiceVol);
		mDeathSound->Play(false);
		Monster::PlayOnDeathSound();
	}
	void Bat::OnLateBeat()
	{
		Monster::OnLateBeat();
		if(mMoveStatus == MoveStatus::Moved)
			mbMove = !mbMove;
	}
	void Bat::SetStats()
	{
		mActivationRadius = 3;
		mMaxHealth = 1;
		mAttackPower = 0.5f;
		mDrop = 2;
	}
	Vector2 Bat::GetNextDir()
	{
		if (!mbMove) {
			return Vector2::Zero;
		}
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