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
		mTransform->SetScale(Vector2::One * UNITSCALE);
	}
	GreenSlime::~GreenSlime()
	{
	}
	void GreenSlime::Initialize()
	{
		Monster::Initialize();
		mSlimeSprite = object::Instantiate<GreenSlimeSprite>(GameObject::GetScene(), mTransform, mTransform->GetPos(), eLayerType::Monster);
		mSprite = mSlimeSprite;
		BeatManager::AddCharacters(this);
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
		Monster::OnBeat();
	}
	bool GreenSlime::TryMove(Vector2 direction)
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
