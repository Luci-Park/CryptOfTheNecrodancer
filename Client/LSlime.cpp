#include "LSlime.h"
#include "LResources.h"
#include "LAudioClip.h"
namespace cl
{
	Slime::Slime(Scene* sc)
		:Monster(sc, true)
	{
		std::wstring path = L"..\\Assets\\Audio\\SoundEffects\\Enemies\\Monsters\\Slime\\en_slime_";
		std::wstring extend = L".wav";
		mSlimeAttackSound = Resources::Load<AudioClip>(L"SlimeAttack", path + L"attack" + extend);
		std::wstring fileName = L"death_0";
		for (int i = 0; i < 3; ++i)
		{
			std::wstring fullPath = path + fileName + std::to_wstring(i + 1) + extend;
			mSlimeDeathSound[i] = Resources::Load<AudioClip>(L"SlimeDeath" + std::to_wstring(i + 1), fullPath);
		}
		fileName = L"hit_0";
		for (int i = 0; i < 3; ++i)
		{
			std::wstring fullPath = path + fileName + std::to_wstring(i + 1) + extend;
			mSlimeHitSound[i] = Resources::Load<AudioClip>(L"SlimeHit" + std::to_wstring(i + 1), fullPath);
		}
	}
	Slime::~Slime()
	{
	}
	void cl::Slime::PlayOnAttackSound()
	{
		mSlimeAttackSound->Play(false);
	}
	void Slime::PlayOnHitSound()
	{
		int index = GetRandomInt(0, 2);
		mSlimeHitSound[index]->Play(false);
	}
	void Slime::PlayOnDeathSound()
	{
		int index = GetRandomInt(0, 2);
		mSlimeDeathSound[index]->Play(false);
	}
}