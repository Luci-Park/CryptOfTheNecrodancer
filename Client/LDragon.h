#pragma once
#include "LDragonBase.h"
namespace cl
{
	class GreenDragon : public DragonBase
	{
	public:
		GreenDragon(Scene* sc);
		virtual ~GreenDragon();

	protected:
		virtual void SetStats() override;
	};
	class RedDragon : public DragonBase
	{
	public:
		RedDragon(Scene* sc);
		virtual ~RedDragon();

	protected:
		virtual void SetStats() override;
		virtual Vector2 GetNextDir() override;
		Vector2 IsInSight();
		void ShootFireball();

	};
}

