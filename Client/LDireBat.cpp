#include "LDireBat.h"
namespace cl
{
	YellowDireBat::YellowDireBat(Scene* sc)
		:DireBatBase(sc)
	{
	}
	YellowDireBat::~YellowDireBat()
	{
	}
	void YellowDireBat::SetStats()
	{
		mActivationRadius = 3;
		mMaxHealth = 2;
		mAttackPower = 1.5;
		mDrop = 10;
	}
	BrownDireBat::BrownDireBat(Scene* sc)
		:DireBatBase(sc)
	{
	}
	BrownDireBat::~BrownDireBat()
	{
	}
	void BrownDireBat::SetStats()
	{
		mActivationRadius = 3;
		mMaxHealth = 3;
		mAttackPower = 2;
		mDrop = 15;
	}
}
