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
#include "LDeepBluesFactory.h"
namespace cl
{
    std::vector<std::vector<eMonsterTypes>> MonsterFactory::_ZoneMonsters =
    {
        {
            eMonsterTypes::GreenSlime, eMonsterTypes::BlueSlime,
            eMonsterTypes::BlueBat, eMonsterTypes::RedBat,
            eMonsterTypes::WhiteSkeleton, eMonsterTypes::YellowSkeleton, eMonsterTypes::BlackSkeleton,
            eMonsterTypes::Zombie
        },
        {
            eMonsterTypes::GreenSlime, eMonsterTypes::BlueSlime, eMonsterTypes::OrangeSlime,
            eMonsterTypes::BlueBat, eMonsterTypes::RedBat,
            eMonsterTypes::WhiteSkeleton, eMonsterTypes::YellowSkeleton, eMonsterTypes::BlackSkeleton,
            eMonsterTypes::Zombie
        },
        {
            eMonsterTypes::GreenSlime, eMonsterTypes::OrangeSlime,
            eMonsterTypes::BlueBat, eMonsterTypes::RedBat,
            eMonsterTypes::YellowSkeleton, eMonsterTypes::BlackSkeleton,
            eMonsterTypes::Zombie
        }
    };
    std::vector<std::vector<eMonsterTypes>> MonsterFactory::_ZoneMiniBosses =
    {
        {
            eMonsterTypes::LightMinotaur,
            eMonsterTypes::YellowDireBat,
            eMonsterTypes::GreenDragon
        },
        {
            eMonsterTypes::DarkMinotaur,
            eMonsterTypes::BrownDireBat,
            eMonsterTypes::RedDragon
        },
        {
            eMonsterTypes::DarkMinotaur,
            eMonsterTypes::RedDragon
        }
    };
    TileObject* MonsterFactory::CreateMonster(eMonsterTypes type, Vector2 index, Scene* scene)
    {
        Vector2 pos = index * UNITLENGTH;
        TileObject* monster = nullptr;
        if (eMonsterTypes::BlueBat == type)
            monster = object::Instantiate<BlueBat>(scene, pos, eLayerType::Monster);
        else if (eMonsterTypes::RedBat == type)
            monster = object::Instantiate<RedBat>(scene, pos, eLayerType::Monster);
        else if (eMonsterTypes::WhiteSkeleton == type)
            monster = object::Instantiate<WhiteSkeleton>(scene, pos, eLayerType::Monster);
        else if (eMonsterTypes::YellowSkeleton == type)
            monster = object::Instantiate<YellowSkeleton>(scene, pos, eLayerType::Monster);
        else if (eMonsterTypes::BlackSkeleton == type)
            monster = object::Instantiate<BlackSkeleton>(scene, pos, eLayerType::Monster);
        else if (eMonsterTypes::BlueSlime == type)
            monster = object::Instantiate<BlueSlime>(scene, pos, eLayerType::Monster);
        else if (eMonsterTypes::GreenSlime == type)
            monster = object::Instantiate<GreenSlime>(scene, pos, eLayerType::Monster);
        else if (eMonsterTypes::OrangeSlime == type)
            monster = object::Instantiate<OrangeSlime>(scene, pos, eLayerType::Monster);
        else if (eMonsterTypes::Zombie == type)
            monster = object::Instantiate<Zombie>(scene, pos, eLayerType::Monster);
        else if (eMonsterTypes::YellowDireBat == type)
            monster = object::Instantiate<YellowDireBat>(scene, pos, eLayerType::Monster);
        else if (eMonsterTypes::BrownDireBat == type)
            monster = object::Instantiate<BrownDireBat>(scene, pos, eLayerType::Monster);
        else if (eMonsterTypes::LightMinotaur == type)
            monster = object::Instantiate<LightMinotaur>(scene, pos, eLayerType::Monster);
        else if (eMonsterTypes::DarkMinotaur == type)
            monster = object::Instantiate<DarkMinotaur>(scene, pos, eLayerType::Monster);
        else if (eMonsterTypes::GreenDragon == type)
            monster = object::Instantiate<GreenDragon>(scene, pos, eLayerType::Monster);
        else if (eMonsterTypes::RedDragon == type)
            monster = object::Instantiate<RedDragon>(scene, pos, eLayerType::Monster);
        else if (eMonsterTypes::DeepBlues == type)
        {
            monster = DeepBluesFactory::CreateBoss(index, scene);
            return monster;
        }
        if (monster != nullptr)
            monster->SetIndex(index);
        
        return monster;
    }

    eMonsterTypes MonsterFactory::GetRandomMonster(int zone)
    {
        if (zone > 3) return eMonsterTypes::None;
        int index = GetRandomInt(0, _ZoneMonsters[zone - 1].size() - 1);
        return _ZoneMonsters[zone - 1][index];
    }
    
    eMonsterTypes MonsterFactory::GetRandomMiniBoss(int zone)
    {
        if (zone > 3) return eMonsterTypes::None;
        int index = GetRandomInt(0, _ZoneMiniBosses[zone - 1].size() - 1);
        return _ZoneMiniBosses[zone - 1][index];
    }
}
