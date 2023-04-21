#pragma once
#include "LMonster.h"
namespace cl
{
	class DragonBase : public Monster
	{
	public:
		enum class State{Idle, ReadyFire, Fire};
		DragonBase(Scene* sc);
		virtual ~DragonBase();

	protected:
	};
}

