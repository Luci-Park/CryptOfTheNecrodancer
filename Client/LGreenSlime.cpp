#include "LGreenSlime.h"
#include "LGreenSlimeSprite.h"
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
	void GreenSlime::SetStats()
	{
		mActivationRadius = INFINITY;
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
