#include "LCadenceSound.h"
#include "LResources.h"
#include "LAudioClip.h"
namespace cl
{
	CadenceSound::CadenceSound()
	{
		SetAudioClip();
	}
	CadenceSound::~CadenceSound()
	{
	}
	void CadenceSound::PlayOnDigSound()
	{
		int random = GetRandomInt(0, mDigVoice.size() - 1);
		mDigVoice[random]->SetVolume(25.f);
		mDigVoice[random]->Play(false);
	}
	void CadenceSound::PlayMeleeSound(int hits)
	{
		if (hits >= mMeleeHitVoice.size()) 
			hits = mMeleeHitVoice.size() - 1;
		int random = GetRandomInt(0, mMeleeHitVoice[0].size() - 1);

		mMeleeHitVoice[hits][random]->Play(false);
	}
	void CadenceSound::PlayRangedSound()
	{
		int random = GetRandomInt(0, mRangedHitVoice.size() - 1);
		mRangedHitVoice[random]->Play(false);
	}
	void CadenceSound::PlayOnHitSound()
	{
		mHitSFX->Play(false);
		int random = GetRandomInt(0, mOnAttackedVoice.size() - 1);
		mOnAttackedVoice[random]->Play(false);
	}
	void CadenceSound::PlayOnDeathSound()
	{
		mDeathSFX->Play(false);
		int random = GetRandomInt(0, mDeathVoice.size() - 1);
		mDeathVoice[random]->Play(false);
	}
	void CadenceSound::SetAudioClip()
	{
		SetDigSound();
		SetAttackSound();
		SetDeathSound();
		SetOnHitSound();
		mDeathSFX = Resources::Load<AudioClip>(L"PlayerHit", L"..\\Assets\\Audio\\SoundEffects\\SFX\\sfx_player_death_ST.wav");
		mHitSFX = Resources::Load<AudioClip>(L"PlayerHit", L"..\\Assets\\Audio\\SoundEffects\\SFX\\sfx_player_hit_ST.wav");	
	}
	void CadenceSound::SetDigSound()
	{
		mDigVoice.resize(6);
		std::wstring cad = L"vo_cad_";
		std::wstring key = cad + L"dig_0";
		std::wstring path = L"..\\Assets\\Audio\\SoundEffects\\CadenceVoice\\";

		for (int i = 0; i < mDigVoice.size(); ++i)
		{
			std::wstring newKey = key + std::to_wstring(i + 1);
			std::wstring newPath = path + newKey + L".wav";
			mDigVoice[i] = Resources::Load<AudioClip>(newKey, newPath);
		}
	}
	void CadenceSound::SetAttackSound()
	{
		mMeleeHitVoice.resize(4);
		std::wstring cad = L"vo_cad_";
		std::wstring key = cad + L"melee_";
		std::wstring path = L"..\\Assets\\Audio\\SoundEffects\\CadenceVoice\\";
		for (int i = 0; i < mMeleeHitVoice.size(); ++i)
		{
			mMeleeHitVoice[i].resize(4);
			std::wstring number = std::to_wstring(i + 1) + L"_0";
			for (int j = 0; j < mMeleeHitVoice[i].size(); j++)
			{
				std::wstring newKey = key + number + std::to_wstring(j + 1);
				std::wstring newPath = path + newKey + L".wav";
				mMeleeHitVoice[i][j] = Resources::Load<AudioClip>(newKey, newPath);
			}
		}

		mRangedHitVoice.resize(7);
		key = cad + L"ranged_0";
		for (int i = 0; i < mRangedHitVoice.size(); ++i)
		{
			std::wstring newKey = key + std::to_wstring(i + 1);
			std::wstring newPath = path + newKey + L".wav";
			mRangedHitVoice[i] = Resources::Load<AudioClip>(newKey, newPath);
		}
	}
	void CadenceSound::SetDeathSound()
	{
		mDeathVoice.resize(3);
		std::wstring cad = L"vo_cad_";
		std::wstring key = cad + L"death_0";
		std::wstring path = L"..\\Assets\\Audio\\SoundEffects\\CadenceVoice\\";

		for (int i = 0; i < mDeathVoice.size(); ++i)
		{
			std::wstring newKey = key + std::to_wstring(i + 1);
			std::wstring newPath = path + newKey + L".wav";
			mDeathVoice[i] = Resources::Load<AudioClip>(newKey, newPath);
		}
	}
	void CadenceSound::SetOnHitSound()
	{
		mOnAttackedVoice.resize(3);
		std::wstring cad = L"vo_cad_";
		std::wstring key = cad + L"hurt_0";
		std::wstring path = L"..\\Assets\\Audio\\SoundEffects\\CadenceVoice\\";

		for (int i = 0; i < mOnAttackedVoice.size(); ++i)
		{
			std::wstring newKey = key + std::to_wstring(i + 1);
			std::wstring newPath = path + newKey + L".wav";
			mOnAttackedVoice[i] = Resources::Load<AudioClip>(newKey, newPath);
		}
	}
}