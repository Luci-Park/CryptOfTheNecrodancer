#include "LPieces.h"
#include "LPiecesSprite.h"
namespace cl
{
	Pieces::Pieces(Scene* sc)
		: Monster(sc, true)
		, mBeatCount(-1)
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
		mLightSource = new LightSource(mTransform, 2.0, 2.0);
	}
	Pieces::~Pieces()
	{
		delete mLightSource;
		mLightSource = nullptr;
	}
	void Pieces::SetStats()
	{
		mMaxHealth = 1;
		mAttackPower = 1;
	}
	void Pieces::PlayOnAttackSound()
	{
		mAttackSound->Play(false);
	}
	void Pieces::PlayOnHitSound()
	{
		mAttackSound->Play(false);
		Monster::PlayOnHitSound();
	}
	void Pieces::PlayOnDeathSound()
	{
		mAttackSound->Play(false);
		Monster::PlayOnDeathSound();
	}
	void Pieces::OnBeat()
	{
		if (mbIsActivated || mbIsAggroed)
		{
			if (mBeatCount == -1 || mBeatCount % mMoveBeat == mMoveBeat - 1)
				mPieceSprite->Ready();
			else
				mPieceSprite->Idle();
			Monster::OnBeat();
			mBeatCount++;
		}
	}
}