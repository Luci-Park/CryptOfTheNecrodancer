#pragma once
#include "LSprite.h"
namespace cl
{
	class WallTile;
	class AudioClip;
	class Tool
	{
	public:
		enum class eShovelTypes {
			Shovel,
			Titanium,
			Glass,
			Obsedian1,
			Obsedian2,
			Obsedian3,
			Blood,
			Crystal,
			Shattered,
			Pickaxe,
			Size = 14
		};
		static Sprite GetShovelSprite(eShovelTypes type, bool isShadow);
	private:
		static Sprite shovelSprites[];

	public:
		Tool(){}
		virtual ~Tool(){}

		virtual bool Dig(WallTile* object) = 0;

		eShovelTypes GetType() { return mTypes; }
	protected:
		int mDigPower;
		eShovelTypes mTypes;
		AudioClip* mDigFailedClip;
	};
	class Shovel : public Tool
	{
	public:
		Shovel();
		virtual ~Shovel();

		virtual bool Dig(WallTile* object);
	};

	class TitaniumShovel : public Tool
	{
	public:
		TitaniumShovel();
		virtual ~TitaniumShovel();

		virtual bool Dig(WallTile* object);
	};

	class CrystalShovel : public Tool
	{
	public:
		CrystalShovel();
		virtual ~CrystalShovel();

		virtual bool Dig(WallTile* object);
	};

	class ObsidianShovel : public Tool
	{
	public:
		ObsidianShovel();
		virtual ~ObsidianShovel();

		virtual bool Dig(WallTile* object);
	};

	class PickAxe : public Tool
	{
	public:
		PickAxe();
		virtual ~PickAxe();

		virtual bool Dig(WallTile* object);
	};
}

