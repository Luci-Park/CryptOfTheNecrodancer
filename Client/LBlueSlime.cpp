#include "LBlueSlime.h"
#include "LBlueSlimeSprite.h"
namespace cl
{
	BlueSlime::BlueSlime(Scene* sc)
		: Slime(sc)
	{
		nextPos.resize(4);
		nextPos[0] = Vector2::Up;
		nextPos[1] = Vector2::Zero;
		nextPos[2] = Vector2::Down;
		nextPos[3] = Vector2::Zero;
		mMovementIndex = 0;
	}
	BlueSlime::~BlueSlime()
	{
	}
	void BlueSlime::Initialize()
	{
		Monster::Initialize();
		mSlimeSprite = object::Instantiate<BlueSlimeSprite>(GameObject::GetScene(), mTransform, mTransform->GetPos(), eLayerType::Monster);
		mSprite = mSlimeSprite;
	}
	void BlueSlime::Update()
	{
		Monster::Update();
	}
	void BlueSlime::Render(HDC hdc)
	{
		Monster::Render(hdc);
	}
	void BlueSlime::Sink()
	{
		Monster::Sink();
	}

	void BlueSlime::OnBeat()
	{
		Monster::OnBeat();
	}
	void BlueSlime::OnLateBeat()
	{
		Monster::OnLateBeat();
		if (mNextDir == Vector2::Zero)
			mSlimeSprite->Idle();
		if (mMoveState != MoveState::Failed)
			mMovementIndex = (mMovementIndex + 1) % nextPos.size();
	}
	void BlueSlime::SetStats()
	{
		mActivationRadius = INFINITY;
		mMaxHealth = 2;
		mAttackPower = 1;
		mDigPower = 0;
		mDrop = 2;
	}
	Vector2 BlueSlime::GetNextDir()
	{
		Vector2 movement = nextPos[mMovementIndex];
		return movement;
	}
}
