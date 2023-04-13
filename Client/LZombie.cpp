#include "LZombie.h"
#include "LZombieSprite.h"
#include "LAudioClip.h"
#include "LResources.h"
#include "LObject.h"
#include "LMapManager.h"
namespace cl
{
	Zombie::Zombie(Scene* sc)
		: Monster(sc, true)
		, mbBeat(true)
	{
		mMoveDir = Vector2::Right;//GetRandomInt(0, 1) ? Vector2::Down : Vector2::Right;
		std::wstring path = L"..\\Assets\\Audio\\SoundEffects\\Enemies\\Monsters\\Zombie\\";
		std::wstring extend = L".wav";
		mAttackSound = Resources::Load<AudioClip>(L"en_zombie_attack", path + L"en_zombie_attack" + extend);
		mDeathSound = Resources::Load<AudioClip>(L"en_zombie_death", path + L"en_zombie_death" + extend);
	}
	Zombie::~Zombie()
	{
	}
	void Zombie::Initialize()
	{
		Monster::Initialize();
		mZombieSprite = object::Instantiate<ZombieSprite>(GameObject::GetScene(), mTransform, mTransform->GetPos(), eLayerType::Monster);
		mSprite = mZombieSprite;
		mSprite->Turn(mMoveDir);
		mZombieSprite->OnBeat();
	}
	void Zombie::PlayOnAttackSound()
	{
		mAttackSound->Play(false);
	}
	void Zombie::PlayOnHitSound()
	{
	}
	void Zombie::PlayOnDeathSound()
	{
		mDeathSound->Play(false);
	}
	void Zombie::SetStats()
	{
		mMaxHealth = 1;
		mAttackPower = 1;
		mDrop = 1;
	}
	Vector2 Zombie::GetNextDir()
	{
		Vector2 targ;
		if (mbBeat)
		{
			mZombieSprite->OnBeat();
			targ = Vector2::Zero;
		}
		else
		{
			mZombieSprite->Idle();
			targ = mMoveDir;
		}
		mbBeat = !mbBeat;
		return targ;

	}
	void Zombie::MoveFailed(Vector2 dir)
	{
		if (mbMoveFailed)
		{
			mMoveDir *= -1;
			mSprite->Turn(mMoveDir);
		}
		GameCharacter::MoveFailed(dir);
	}
}