#include "LShovel.h"
#include "LWallTile.h"
namespace cl
{
	Sprite Shovel::shovelSprites[(int)eShovelTypes::Size] =
	{
		//Sprite(Vector2 lefttop, Vector2 size, Vector2 offset)
		{Vector2(0, 3), Vector2(24, 24), Vector2(-12, -12)},
		{Vector2(29, 3), Vector2(24, 24), Vector2(-12, -12)},
		{Vector2(58, 3), Vector2(24, 24), Vector2(-12, -12)},
		{Vector2(87, 2), Vector2(24, 24), Vector2(-12, -12)},
		{Vector2(112, 1), Vector2(26, 26), Vector2(-13, -13)},
		{Vector2(138, 1), Vector2(26, 26), Vector2(-13, -13)},
		{Vector2(169, 3), Vector2(24, 24), Vector2(-12, -12)},
		{Vector2(198, 3), Vector2(24, 24), Vector2(-12, -12)},
		{Vector2(227, 6), Vector2(9, 18), Vector2(-5, -9)},
		{Vector2(241, 3), Vector2(23, 24), Vector2(-12, -12)}
	};
	Sprite Shovels::GetShovelSprite(eShovelTypes type, bool isShadow)
	{
		Sprite sprite = shovelSprites[(int)type];
		return sprite;
	}
	Shovel::Shovel()
	{
		mDigPower = 10;
		mTypes = eShovelTypes::Shovel;
	}
	Shovel::~Shovel()
	{
	}
	bool Shovel::Dig(WallTile* object)
	{
		if (object != nullptr)
		{
			return object->OnDig(mDigPower);
		}
	}
	TitaniumShovel::TitaniumShovel()
	{
		mDigPower = 2;
		mTypes = eShovelTypes::Titanium;
	}
	TitaniumShovel::~TitaniumShovel()
	{
	}
	bool TitaniumShovel::Dig(WallTile* object)
	{
		if (object != nullptr)
		{
			return object->OnDig(mDigPower);
		}
	}
	CrystalShovel::CrystalShovel()
	{
		mDigPower = 3;
		mTypes = eShovelTypes::Crystal;
	}
	CrystalShovel::~CrystalShovel()
	{
	}
	bool CrystalShovel::Dig(WallTile* object)
	{
		if (object != nullptr)
		{
			return object->OnDig(mDigPower);
		}
	}
	ObsidianShovel::ObsidianShovel()
	{
		mDigPower = 2;
		mTypes = eShovelTypes::Obsedian1;
	}
	ObsidianShovel::~ObsidianShovel()
	{
	}
	bool ObsidianShovel::Dig(WallTile* object)
	{
		return false;
	}
	PickAxe::PickAxe()
	{
	}
	PickAxe::~PickAxe()
	{
	}
	bool PickAxe::Dig(WallTile* object)
	{
		if (object != nullptr)
			return object->OnCrumble();
	}
}