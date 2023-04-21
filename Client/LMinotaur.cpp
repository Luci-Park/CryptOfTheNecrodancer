#include "LMinotaur.h"
namespace cl
{
	LightMinotaur::LightMinotaur(Scene* sc)
		:MinotaurBase(sc)
	{
	}
	LightMinotaur::~LightMinotaur()
	{
	}
	void LightMinotaur::SetStats()
	{
		mActivationRadius = 7;
		mMaxHealth = 3;
		mAttackPower = 2;
		mDigPower = 2;
		mDrop = 10;
	}
	int LightMinotaur::GetY()
	{
		return 0;
	}
	DarkMinotaur::DarkMinotaur(Scene* sc)
		:MinotaurBase(sc)
	{
	}
	DarkMinotaur::~DarkMinotaur()
	{
	}
	void DarkMinotaur::SetStats()
	{
		mActivationRadius = 7;
		mMaxHealth = 5;
		mAttackPower = 2.5;
		mDigPower = 2;
		mDrop = 15;
	}
	int DarkMinotaur::GetY()
	{
		return 1;
	}
}
