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
		static TileObject* CreateMiniBoss(eMidBossTypes type, Vector2 index, Scene* scene);
		static eMidBossTypes GetRandomMiniBoss(int zone);
	private:
		static std::vector<std::vector<eMonsterTypes>> _ZoneMonsters;
		static std::vector<std::vector<eMidBossTypes>> _ZoneBosses;
	};
}
