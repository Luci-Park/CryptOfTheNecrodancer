#include "LZombie.h"
#include "LZombieSprite.h"
namespace cl
{
	Zombie::Zombie(Scene* sc)
		: Monster(sc, true)
		, mbBeat(true)
	{
		mMoveDir = GetRandomInt(0, 1) ? Vector2::Down : Vector2::Right;
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
	void Zombie::OnLateBeat()
	{
		Monster::OnLateBeat();
		if (mMoveState != MoveState::Failed)
			mbBeat = !mbBeat;
		if (mMoveState == MoveState::Dug || mMoveState == MoveState::Failed)
		{
			mMoveDir *= -1;
			mSprite->Turn(mMoveDir);
		}
	}
	void Zombie::PlayOnAttackSound()
	{
		mAttackSound->Play(false);
	}
	void Zombie::PlayOnHitSound()
	{
		Monster::PlayOnHitSound();
	}
	void Zombie::PlayOnDeathSound()
	{
		mDeathSound->Play(false);
		Monster::PlayOnDeathSound();
	}
	void Zombie::SetStats()
	{
		mActivationRadius = INFINITY;
		mMaxHealth = 1;
		mAttackPower = 1;
		mDrop = 1;
	}
}