#include "LSlime.h"
#include "LResources.h"
#include "LAudioClip.h"
namespace cl
{
	Slime::Slime(Scene* sc)
		:Monster(sc, true)
	{
		std::wstring path = L"..\\Assets\\Audio\\SoundEffects\\Enemies\\Monsters\\Slime\\";
		std::wstring extend = L".wav";

		mSlimeAttackSound = Resources::Load<AudioClip>(L"en_slime_attack", path + L"en_slime_attack" + extend);
		std::wstring key = L"en_slime_death_0";
		for (int i = 0; i < 3; ++i)
		{
			std::wstring newKey = key + std::to_wstring(i + 1);
			std::wstring newPath = path + newKey + extend;
			mSlimeDeathSound[i] = Resources::Load<AudioClip>(newKey, newPath);
		}
		key = L"en_slime_hit_0";
		for (int i = 0; i < 3; ++i)
		{
			std::wstring newKey = key + std::to_wstring(i + 1);
			std::wstring newPath = path + newKey + extend;
			mSlimeHitSound[i] = Resources::Load<AudioClip>(newKey, newPath);
		}
	}
	Slime::~Slime()
	{
	}
	void Slime::PlayOnAttackSound()
	{
		mSlimeAttackSound->SetVolume(voiceVol);
		mSlimeAttackSound->Play(false);
	}
	void Slime::PlayOnHitSound()
	{
		int index = GetRandomInt(0, 2);
		mSlimeHitSound[index]->SetVolume(voiceVol);
		mSlimeHitSound[index]->Play(false);
		Monster::PlayOnHitSound();
	}
	void Slime::PlayOnDeathSound()
	{
		int index = GetRandomInt(0, 2);
		mSlimeDeathSound[index]->SetVolume(voiceVol);
		mSlimeDeathSound[index]->Play(false);
		Monster::PlayOnDeathSound();
	}
}