#include "LMonster.h"
#include "LWallTile.h"
namespace cl
{

	Monster::Monster(Scene* sc, bool isFlying)
		:GameCharacter(sc, isFlying)
	{
	}
	Monster::~Monster()
	{
	}
	void Monster::Initialize()
	{
		mHealth = mMaxHealth;
	}
	void Monster::Dig(TileObject* object)
	{
		WallTile* tile = dynamic_cast<WallTile*>(object);
		if (tile != nullptr)
		{
			if (tile->OnDig(mDigPower))
			{
			}
			else {
			}
		}
	}
}
