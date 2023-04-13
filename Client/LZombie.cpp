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
		, mbFlip(false)
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
	}
	bool Zombie::TryAttack(Vector2 Direction)
	{
		bool success = Monster::TryAttack(Direction);
		if (success)
			mbFlip = false;
		return success;
	}
	bool Zombie::TryMove(Vector2 direction)
	{
		bool success = Monster::TryMove(direction);
		if (success) mbFlip = false;
		return success;
	}
	Vector2 Zombie::GetNextDir()
	{
		if (mbBeat)
		{
			mZombieSprite->OnBeat();
			return Vector2::Zero;
		}
		else
		{
			mZombieSprite->Idle();
			return mMoveDir;
		}

	}
	void Zombie::OnBeat()
	{
		mbFlip = true;
		Monster::OnBeat();
	}
	void Zombie::OnLateBeat()
	{
		Monster::OnLateBeat();
		mbBeat = !mbBeat;
		if (mbFlip)
		{
			mMoveDir * -1;
			mSprite->Turn(mMoveDir);
		}
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
}