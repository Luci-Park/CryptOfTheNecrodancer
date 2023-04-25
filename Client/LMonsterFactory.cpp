#include "LMonsterFactory.h"
#include "LObject.h"
#include "LBat.h"
#include "LSkeleton.h"
#include "LBlueSlime.h"
#include "LGreenSlime.h"
#include "LOrangeSlime.h"
#include "LZombie.h"
#include "LDireBat.h"
#include "LMinotaur.h"
#include "LDragon.h"
namespace cl
{
    std::vector<std::vector<MonsterFactory::MonsterType>> MonsterFactory::_ZoneMonsters =
    {
        {
            MonsterType::GreenSlime, MonsterType::BlueSlime,
            MonsterType::BlueBat, MonsterType::RedBat,
            MonsterType::WhiteSkeleton, MonsterType::YellowSkeleton, MonsterType::BlackSkeleton,
            MonsterType::Zombie
        },
        {
            MonsterType::GreenSlime, MonsterType::BlueSlime, MonsterType::OrangeSlime,
            MonsterType::BlueBat, MonsterType::RedBat,
            MonsterType::WhiteSkeleton, MonsterType::YellowSkeleton, MonsterType::BlackSkeleton,
            MonsterType::Zombie
        },
        {
            MonsterType::GreenSlime, MonsterType::OrangeSlime,
            MonsterType::BlueBat, MonsterType::RedBat,
            MonsterType::YellowSkeleton, MonsterType::BlackSkeleton,
            MonsterType::Zombie
        }
    };
    std::vector<std::vector<MonsterFactory::MiniBossType>> MonsterFactory::_ZoneBosses =
    {
        {
            MonsterFactory::MiniBossType::LightMinotaur, 
            MonsterFactory::MiniBossType::YellowDireBat,
            MonsterFactory::MiniBossType::GreenDragon
        },
        {
            MonsterFactory::MiniBossType::DarkMinotaur,
            MonsterFactory::MiniBossType::BrownDireBat,
            MonsterFactory::MiniBossType::RedDragon
        },
        {
            MonsterFactory::MiniBossType::DarkMinotaur,
            MonsterFactory::MiniBossType::RedDragon
        }
    };
    TileObject* MonsterFactory::CreateMonster(MonsterType type, Vector2 index, Scene* scene)
    {
        Vector2 pos = index * UNITLENGTH;
        TileObject* monster = nullptr;
        if(MonsterType::BlueBat == type)
            monster = object::Instantiate<BlueBat>(scene, pos, eLayerType::Monster);
        else if (MonsterType::RedBat == type)
            monster = object::Instantiate<RedBat>(scene, pos, eLayerType::Monster);
        else if (MonsterType::WhiteSkeleton == type)
            monster = object::Instantiate<WhiteSkeleton>(scene, pos, eLayerType::Monster);
        else if (MonsterType::YellowSkeleton == type)
            monster = object::Instantiate<YellowSkeleton>(scene, pos, eLayerType::Monster);
        else if (MonsterType::BlackSkeleton == type)
            monster = object::Instantiate<BlackSkeleton>(scene, pos, eLayerType::Monster);
        else if (MonsterType::BlueSlime == type)
            monster = object::Instantiate<BlueSlime>(scene, pos, eLayerType::Monster);
        else if (MonsterType::GreenSlime == type)
            monster = object::Instantiate<GreenSlime>(scene, pos, eLayerType::Monster);
        else if (MonsterType::OrangeSlime == type)
            monster = object::Instantiate<OrangeSlime>(scene, pos, eLayerType::Monster);
        else if (MonsterType::Zombie == type)
            monster = object::Instantiate<Zombie>(scene, pos, eLayerType::Monster);
 
        if (monster != nullptr)
            monster->SetIndex(index);
        
        return monster;
    }

    MonsterFactory::MonsterType MonsterFactory::GetRandomMonster(int zone)
    {
        if (zone > 3) return MonsterType::None;
        int index = GetRandomInt(0, _ZoneMonsters[zone - 1].size() - 1);
        return _ZoneMonsters[zone - 1][index];
    }
    TileObject* MonsterFactory::CreateMiniBoss(MiniBossType type, Vector2 index, Scene* scene)
    {
        Vector2 pos = index * UNITLENGTH;
        TileObject* monster = nullptr;
        if (MiniBossType::YellowDireBat == type)
            monster = object::Instantiate<YellowDireBat>(scene, pos, eLayerType::Monster);
        if (MiniBossType::BrownDireBat == type)
            monster = object::Instantiate<BrownDireBat>(scene, pos, eLayerType::Monster);
        if (MiniBossType::LightMinotaur == type)
            monster = object::Instantiate<LightMinotaur>(scene, pos, eLayerType::Monster);
        if (MiniBossType::DarkMinotaur == type)
            monster = object::Instantiate<DarkMinotaur>(scene, pos, eLayerType::Monster);
        if (MiniBossType::GreenDragon == type)
            monster = object::Instantiate<GreenDragon>(scene, pos, eLayerType::Monster);
        if (MiniBossType::RedDragon == type)
            monster = object::Instantiate<RedDragon>(scene, pos, eLayerType::Monster);

        if (monster != nullptr)
            monster->SetIndex(index);
        return monster;
    }
    MonsterFactory::MiniBossType MonsterFactory::GetRandomMiniBoss(int zone)
    {
        if (zone > 3) return MiniBossType::None;
        int index = GetRandomInt(0, _ZoneBosses[zone - 1].size() - 1);
        return _ZoneBosses[zone - 1][index];
    }
}
