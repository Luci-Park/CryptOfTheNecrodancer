#pragma once
#include "LDragonBase.h"
namespace cl
{
	class GreenDragon : public DragonBase
	{
	public:
		GreenDragon(Scene* sc);
		virtual ~GreenDragon();
		virtual void Initialize() override;
	protected:
		virtual void SetStats() override;
	};
	class RedDragonSprite;
	class RedDragon : public DragonBase
	{
	public:
		RedDragon(Scene* sc);
		virtual ~RedDragon();
		virtual void Initialize() override;
	protected:
		virtual void SetStats() override;
		virtual Vector2 GetNextDir() override;
		virtual void SetDragonState(State state) override;
		Vector2 IsInSight();
		void ShootFireball();
		RedDragonSprite* mDragonSprite;

	};
}

