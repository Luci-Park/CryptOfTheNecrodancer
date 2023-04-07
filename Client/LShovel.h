#pragma once
#include "LSprite.h"
namespace cl
{
	class WallTile;
	class AudioClip;
	class Shovels
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
		Shovels(){}
		virtual ~Shovels(){}

		virtual bool Dig(WallTile* object) = 0;

		eShovelTypes GetType() { return mTypes; }
	protected:
		int mDigPower;
		eShovelTypes mTypes;
		AudioClip* mDigFailedClip;
	};
	class Shovel : public Shovels
	{
	public:
		Shovel();
		virtual ~Shovel();

		virtual bool Dig(WallTile* object);
	};

	class TitaniumShovel : public Shovels
	{
	public:
		TitaniumShovel();
		virtual ~TitaniumShovel();

		virtual bool Dig(WallTile* object);
	};

	class CrystalShovel : public Shovels
	{
	public:
		CrystalShovel();
		virtual ~CrystalShovel();

		virtual bool Dig(WallTile* object);
	};

	class ObsidianShovel : public Shovels
	{
	public:
		ObsidianShovel();
		virtual ~ObsidianShovel();

		virtual bool Dig(WallTile* object);
	};

	class PickAxe : public Shovels
	{
	public:
		PickAxe();
		virtual ~PickAxe();

		virtual bool Dig(WallTile* object);
	};
}

