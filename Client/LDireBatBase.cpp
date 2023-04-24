#include "LDirebatBase.h"
#include "LDireBatSprite.h"
#include "LMapManager.h"
namespace cl
{
	DireBatBase::DireBatBase(Scene* sc)
		:Monster(sc, false)
	{
		mSize = 2;
		mLightSource = new LightSource(mTransform, 1.0, 1.0);

		std::wstring path = L"..\\Assets\\Audio\\SoundEffects\\Enemies\\Midboss\\Direbat\\";
		std::wstring extend = L".wav";
		mAttackSound = Resources::Load<AudioClip>(L"en_vampbat_attack", path + L"en_vampbat_attack" + extend);
		mCrySound = Resources::Load<AudioClip>(L"en_vampbat_cry", path + L"en_vampbat_cry" + extend);
		mDeathSound = Resources::Load<AudioClip>(L"en_vampbat_death", path + L"en_vampbat_death" + extend);
		std::wstring key = L"en_vampbat_hit_0";
		for (int i = 0; i < 3; ++i)
		{
			std::wstring newKey = key + std::to_wstring(i + 1);
			mHitSounds[i] = Resources::Load<AudioClip>(newKey, path + newKey + extend);
		}
	}
	DireBatBase::~DireBatBase()
	{
		delete mLightSource;
		mLightSource = nullptr;
	}
	void DireBatBase::Initialize()
	{
		Monster::Initialize();
		DireBatSprite* sprite = object::Instantiate<DireBatSprite>(GameObject::GetScene(), mTransform, mTransform->GetPos(), eLayerType::Monster);
		mSprite = sprite;
		sprite->SetY(GetY());
		
	}
	void DireBatBase::OnAggroed()
	{
		mCrySound->Play(false);
	}
	void DireBatBase::OnLateBeat()
	{
		Monster::OnLateBeat();
		if (mMoveState == MoveState::Moved)
			mbMove = !mbMove;		
	}
	void DireBatBase::PlayOnAttackSound()
	{
		mAttackSound->Play(false);
	}
	void DireBatBase::PlayOnHitSound()
	{
		int index = GetRandomInt(0, 2);
		mHitSounds[index]->Play(false);
		Monster::PlayOnHitSound();
	}
	void DireBatBase::PlayOnDeathSound()
	{
		mDeathSound->Play(false);
		Monster::PlayOnDeathSound();
	}
	Vector2 DireBatBase::GetNextDir()
	{
		if (!mbMove) {
			return Vector2::Zero;
		}
		int dx[4] = { 0, 1, 0, -1 };
		int dy[4] = { 1, 0, -1, 0 };
		std::vector<int>possible;
		for (int i = 0; i < 4; i++)
		{
			if (MapManager::GetEnemy(mIndex + Vector2(dx[i], dy[i])) == nullptr
				&& MapManager::GetWall(mIndex + Vector2(dx[i], dy[i])) == nullptr)
				possible.push_back(i);
		}
		if (possible.size() == 0) return Vector2::Zero;
		Vector2 dir;
		int idx = GetRandomInt(0, possible.size() - 1);
		return Vector2(dx[possible[idx]], dy[possible[idx]]);
	}
}