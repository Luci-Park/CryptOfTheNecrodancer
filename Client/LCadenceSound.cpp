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
		int random = GetRandomInt(0, mDigVoices.size() - 1);
		mDigVoices[random]->SetVolume(25.f);
		mDigVoices[random]->Play(false);
	}
	void CadenceSound::PlayMeleeSound(int hits)
	{
		if (hits >= mMeleeHitVoices.size()) 
			hits = mMeleeHitVoices.size() - 1;
		int random = GetRandomInt(0, mMeleeHitVoices[0].size() - 1);

		mMeleeHitVoices[hits][random]->Play(false);
	}
	void CadenceSound::PlayRangedSound()
	{
		int random = GetRandomInt(0, mRangedHitVoices.size() - 1);
		mRangedHitVoices[random]->Play(false);
	}
	void CadenceSound::PlayOnHitSound()
	{
		mHitSFX->Play(false);
		int random = GetRandomInt(0, mOnAttackedVoices.size() - 1);
		mOnAttackedVoices[random]->Play(false);
	}
	void CadenceSound::PlayOnDeathSound()
	{
		mDeathSFX->Play(false);
		int random = GetRandomInt(0, mDeathVoices.size() - 1);
		mDeathVoices[random]->Play(false);
	}
	void CadenceSound::PlayVictorySound()
	{
		int random = GetRandomInt(0, mVictoryVoices.size() - 1);
		mVictoryVoices[random]->Play(false);
	}
	void CadenceSound::SetAudioClip()
	{
		SetDigSound();
		SetAttackSound();
		SetDeathSound();
		SetOnHitSound();
		SetVictorySound();
		mDeathSFX = Resources::Load<AudioClip>(L"PlayerHit", L"..\\Assets\\Audio\\SoundEffects\\SFX\\sfx_player_death_ST.wav");
		mHitSFX = Resources::Load<AudioClip>(L"PlayerHit", L"..\\Assets\\Audio\\SoundEffects\\SFX\\sfx_player_hit_ST.wav");	
	}
	void CadenceSound::SetDigSound()
	{
		mDigVoices.resize(6);
		std::wstring cad = L"vo_cad_";
		std::wstring key = cad + L"dig_0";
		std::wstring path = L"..\\Assets\\Audio\\SoundEffects\\CadenceVoice\\";

		for (int i = 0; i < mDigVoices.size(); ++i)
		{
			std::wstring newKey = key + std::to_wstring(i + 1);
			std::wstring newPath = path + newKey + L".wav";
			mDigVoices[i] = Resources::Load<AudioClip>(newKey, newPath);
		}
	}
	void CadenceSound::SetAttackSound()
	{
		mMeleeHitVoices.resize(4);
		std::wstring cad = L"vo_cad_";
		std::wstring key = cad + L"melee_";
		std::wstring path = L"..\\Assets\\Audio\\SoundEffects\\CadenceVoice\\";
		for (int i = 0; i < mMeleeHitVoices.size(); ++i)
		{
			mMeleeHitVoices[i].resize(4);
			std::wstring number = std::to_wstring(i + 1) + L"_0";
			for (int j = 0; j < mMeleeHitVoices[i].size(); j++)
			{
				std::wstring newKey = key + number + std::to_wstring(j + 1);
				std::wstring newPath = path + newKey + L".wav";
				mMeleeHitVoices[i][j] = Resources::Load<AudioClip>(newKey, newPath);
			}
		}

		mRangedHitVoices.resize(7);
		key = cad + L"ranged_0";
		for (int i = 0; i < mRangedHitVoices.size(); ++i)
		{
			std::wstring newKey = key + std::to_wstring(i + 1);
			std::wstring newPath = path + newKey + L".wav";
			mRangedHitVoices[i] = Resources::Load<AudioClip>(newKey, newPath);
		}
	}
	void CadenceSound::SetDeathSound()
	{
		mDeathVoices.resize(3);
		std::wstring cad = L"vo_cad_";
		std::wstring key = cad + L"death_0";
		std::wstring path = L"..\\Assets\\Audio\\SoundEffects\\CadenceVoice\\";

		for (int i = 0; i < mDeathVoices.size(); ++i)
		{
			std::wstring newKey = key + std::to_wstring(i + 1);
			std::wstring newPath = path + newKey + L".wav";
			mDeathVoices[i] = Resources::Load<AudioClip>(newKey, newPath);
		}
	}
	void CadenceSound::SetOnHitSound()
	{
		mOnAttackedVoices.resize(3);
		std::wstring cad = L"vo_cad_";
		std::wstring key = cad + L"hurt_0";
		std::wstring path = L"..\\Assets\\Audio\\SoundEffects\\CadenceVoice\\";

		for (int i = 0; i < mOnAttackedVoices.size(); ++i)
		{
			std::wstring newKey = key + std::to_wstring(i + 1);
			std::wstring newPath = path + newKey + L".wav";
			mOnAttackedVoices[i] = Resources::Load<AudioClip>(newKey, newPath);
		}
	}
	void CadenceSound::SetVictorySound()
	{
		mVictoryVoices.resize(5);
		std::wstring cad = L"vo_cad_";
		std::wstring key = cad + L"yeah_0";
		std::wstring path = L"..\\Assets\\Audio\\SoundEffects\\CadenceVoice\\";

		for (int i = 0; i < mVictoryVoices.size(); ++i)
		{
			std::wstring newKey = key + std::to_wstring(i + 1);
			std::wstring newPath = path + newKey + L".wav";
			mVictoryVoices[i] = Resources::Load<AudioClip>(newKey, newPath);
		}
	}
}