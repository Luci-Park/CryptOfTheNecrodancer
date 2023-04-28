#pragma once
#include "LuciEngine.h"
namespace cl
{
	class TileObject;
	class Scene;
	class MonsterFactory
	{
	public:
		static TileObject* CreateMonster(eMonsterTypes type, Vector2 index, Scene* scene);
		static eMonsterTypes GetRandomMonster(int zone);
		static eMonsterTypes GetRandomMiniBoss(int zone);
	private:
		static std::vector<std::vector<eMonsterTypes>> _ZoneMonsters;
		static std::vector<std::vector<eMonsterTypes>> _ZoneMiniBosses;
	};
}
