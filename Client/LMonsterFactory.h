#pragma once
#include "LuciEngine.h"
namespace cl
{
	class TileObject;
	class Scene;
	class MonsterFactory
	{
	public:
		enum class MonsterType
		{
			BlueBat, RedBat,
			WhiteSkeleton, YellowSkeleton, BlackSkeleton,
			BlueSlime, GreenSlime, OrangeSlime,
			Zombie,
			None
		};

		enum class MiniBossType
		{
			 YellowDireBat, BrownDireBat,
			 LightMinotaur, DarkMinotaur,
			 GreenDragon, RedDragon,
			 None
		};
		static TileObject* CreateMonster(MonsterType type, Vector2 index, Scene* scene);
		static MonsterType GetRandomMonster(int zone);
		static TileObject* CreateMiniBoss(MiniBossType type, Vector2 index, Scene* scene);
		static MiniBossType GetRandomMiniBoss(int zone);
	private:
		static std::vector<std::vector<MonsterType>> _ZoneMonsters;
		static std::vector<std::vector<MiniBossType>> _ZoneBosses;
	};
}
