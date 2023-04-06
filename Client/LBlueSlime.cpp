#include "LBlueSlime.h"
#include "LBlueSlimeSprite.h"
#include "LObject.h"
#include "LMapManager.h"
#include "LBeatManager.h"
#include "LCadence.h"
namespace cl
{
	BlueSlime::BlueSlime(Scene* sc)
		: Slime(sc)
	{
		mTransform->SetScale(Vector2::One * UNITSCALE);
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
		BeatManager::AddCharacters(this);
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
	bool BlueSlime::TryMove(Vector2 direction)
	{
		if (direction == Vector2::Zero)
			mSlimeSprite->Idle();
		else
		{
			mMoveTarget += direction * UNITLENGTH;
			mSlimeSprite->Jump();
			MapManager::Move(mIndex, mIndex + direction);
			mIndex += direction;
		}
		mMovementIndex = (mMovementIndex + 1) % nextPos.size();
		return true;
	}
	void BlueSlime::SetStats()
	{
		mMaxHealth = 2;
		mHealth = 2;
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
