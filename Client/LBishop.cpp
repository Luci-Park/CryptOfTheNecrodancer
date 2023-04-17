#include "LBishop.h"
#include "LAudioClip.h"
#include "LResources.h"
#include "LObject.h"
#include "LBishopSprite.h"
#include "LMapManager.h"
#include "LCadence.h"
namespace cl
{
	Bishop::Bishop(Scene* sc)
		: Monster(sc, true)
		, mMoveBeat(4)
	{
		std::wstring path = L"..\\Assets\\Audio\\SoundEffects\\Enemies\\Boss\\DeepBlues\\";
		std::wstring extend = L".wav";

		mAttackSound = Resources::Load<AudioClip>(L"en_blues_piece_attack", path + L"en_blues_piece_attack" + extend);
		std::wstring key = L"en_blues_piece_death_0";
		for (int i = 0; i < 3; ++i)
		{
			std::wstring nKey = key + std::to_wstring(i + 1);
			mDeathSounds[i] = Resources::Load<AudioClip>(nKey, path + nKey + extend);
		}
	}
	Bishop::~Bishop()
	{
	}
	void Bishop::Initialize()
	{
		Monster::Initialize();
		mBishopSprite = object::Instantiate<BishopSprite>(GameObject::GetScene(), mTransform, mTransform->GetPos(), eLayerType::Monster);
	}
	Vector2 Bishop::GetNextDir()
	{
		if (mBeatCount == mMoveBeat)
		{
			Vector2 playerIndex = MapManager::GetPlayerIndex();
			Vector2 dir = (playerIndex - mIndex).TileNormalize();
			if (Vector2::IsDiagonal(dir))
				return dir;
			else
			{
				Vector2 prevPlayerPos = playerIndex - MapManager::GetPlayer(playerIndex)->GetInput();
				Vector2 prevDir = (prevPlayerPos - mIndex).TileNormalize();
				if (Vector2::IsDiagonal(prevDir))
					return prevDir;
				else
				{
					if (dir.y == 0)
						dir.y == 1;
					else if (dir.x == 0)
						dir.x == -1;
					return dir;
				}
			}
		}
		return Vector2::Zero;
	}
	void Bishop::SetStats()
	{
		mMaxHealth = 1;
		mAttackPower = 1;
	}
	void Bishop::PlayOnAttackSound()
	{
		mAttackSound->Play(false);
	}
	void Bishop::PlayOnHitSound()
	{
		mAttackSound->Play(false);
	}
	void Bishop::PlayOnDeathSound()
	{
		int idx = GetRandomInt(0, 2);
		mDeathSounds[idx]->Play(false);
	}
	void Bishop::OnBeat()
	{
		if (mBeatCount == mMoveBeat - 2)
			mBishopSprite->Ready();
		else
			mBishopSprite->Idle();
		Monster::OnBeat();
		mBeatCount = (mBeatCount + 1) % mMoveBeat;
	}
}
