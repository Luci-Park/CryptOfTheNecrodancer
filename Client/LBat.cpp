#include "LBat.h"
#include "LBatSprite.h"
#include "LRedBatSprite.h"
namespace cl
{
	BlueBat::BlueBat(Scene* sc)
		:BatBase(sc)
		, mbMove(true)
	{
	}
	BlueBat::~BlueBat()
	{
	}
	void BlueBat::Initialize()
	{
		Monster::Initialize();
		mSprite = object::Instantiate<BatSprite>(GameObject::GetScene(), mTransform, mTransform->GetPos(), eLayerType::Monster);
	}
	void BlueBat::OnLateBeat()
	{
		Monster::OnLateBeat();
		if(mMoveState != MoveState::Failed)
			mbMove = !mbMove;
	}
	void BlueBat::SetStats()
	{
		mActivationRadius = 3;
		mMaxHealth = 1;
		mAttackPower = 0.5f;
		mDrop = 2;
	}
	Vector2 BlueBat::GetNextDir()
	{
		if (!mbMove) {
			return Vector2::Zero;
		}
		else
		{
			return BatBase::GetNextDir();
		}
	}

	RedBat::RedBat(Scene* sc)
		:BatBase(sc)
	{
	}

	RedBat::~RedBat()
	{
	}

	void RedBat::Initialize()
	{
		Monster::Initialize();
		mSprite = object::Instantiate<RedBatSprite>(GameObject::GetScene(), mTransform, mTransform->GetPos(), eLayerType::Monster);
	}

	void RedBat::SetStats()
	{
		mActivationRadius = 3;
		mMaxHealth = 1;
		mAttackPower = 1.0f;
		mDrop = 3;
	}
}