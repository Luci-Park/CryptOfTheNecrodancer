#include "LGreenSlime.h"
#include "LGreenSlimeSprite.h"
#include "LObject.h"
#include "LMapManager.h"
#include "LBeatManager.h"
#include "LCadence.h"
#include "LResources.h"
#include "LAudioClip.h"
namespace cl
{
	GreenSlime::GreenSlime(Scene* sc)
		: Slime(sc)
	{
	}
	GreenSlime::~GreenSlime()
	{
	}
	void GreenSlime::Initialize()
	{
		Monster::Initialize();
		mSlimeSprite = object::Instantiate<GreenSlimeSprite>(GameObject::GetScene(), mTransform, mTransform->GetPos(), eLayerType::Monster);
		mSprite = mSlimeSprite;
	}
	void GreenSlime::Update()
	{
		Monster::Update();
	}
	void GreenSlime::Render(HDC hdc)
	{
		Monster::Render(hdc);
	}
	void GreenSlime::Sink()
	{
		Monster::Sink();
	}
	void GreenSlime::OnBeat()
	{
	}
	bool GreenSlime::TryMove()
	{
		if (mNextDir == Vector2::Zero)
			mSlimeSprite->Idle();
		else
		{
			Monster::TryMove();
		}
		return true;
	}
	void GreenSlime::SetStats()
	{
		mMaxHealth = 1;
		mHealth = 1;
		mAttackPower = 50;
		mDigPower = 0;
		mDrop = 1;
	}
	Vector2 GreenSlime::GetNextDir()
	{
		return Vector2::Zero;
	}
}
