#include "LOrangeSlime.h"
#include "LOrangeSlimeSprite.h"
#include "LObject.h"
#include "LMapManager.h"
#include "LBeatManager.h"
#include "LCadence.h"
namespace cl
{
	OrangeSlime::OrangeSlime(Scene* sc)
		: Slime(sc)
	{
		nextPos.resize(4);
		nextPos[0] = Vector2::Up;
		nextPos[1] = Vector2::Right;
		nextPos[2] = Vector2::Down;
		nextPos[3] = Vector2::Left;
		mMovementIndex = 0;
	}
	
	OrangeSlime::~OrangeSlime()
	{
	}
	
	void OrangeSlime::Initialize()
	{
		Monster::Initialize();
		mSlimeSprite = object::Instantiate<OrangeSlimeSprite>(GameObject::GetScene(), mTransform, mTransform->GetPos(), eLayerType::Monster);
		mSprite = mSlimeSprite;
	}
	
	void OrangeSlime::Update()
	{
		Monster::Update();
	}
	
	void OrangeSlime::Render(HDC hdc)
	{
		Monster::Render(hdc);
	}
	
	void OrangeSlime::Sink()
	{
		Monster::Sink();
	}

	void OrangeSlime::OnBeat()
	{
		Monster::OnBeat();
	}

	bool OrangeSlime::TryMove(Vector2 direction)
	{
		mMoveTarget += direction * UNITLENGTH;
		mSlimeSprite->Jump();
		MapManager::Move(mIndex, mIndex + direction);
		mIndex += direction;
		mMovementIndex = (mMovementIndex + 1) % nextPos.size();
		return true;
	}
	
	void OrangeSlime::SetStats()
	{
		mMaxHealth = 1;
		mHealth = 1;
		mAttackPower = 0.5;
		mDigPower = 0;
		mDrop = 2;
	}
	
	Vector2 OrangeSlime::GetNextDir()
	{
		Vector2 movement = nextPos[mMovementIndex];
		return movement;
	}
}
