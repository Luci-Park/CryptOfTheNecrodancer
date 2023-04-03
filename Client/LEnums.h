#pragma once


enum class eSceneType
{
	Splash,
	Title,
	Lobby,
	Tutorial,
	Depth1,
	Depth2,
	Depth3,
	BossRoom,
	Size
};

enum class eLayerType
{
	System,
	Background,
	Player,
	Monster,
	Wall,
	Effects,
	UI,
	Size,
};

enum class eComponentType
{
	Transform,
	SpriteRenderer,
	Animator,
	Collider,
	Audio,
	Size
};

enum class eMonsterTypes {
	Bat, RedBat,
	Ghost,
	Monkey, WhiteMonkey,
	Skeleton, YellowSkeleton, BlackSkeleton,
	GreenSlime, BlueSlime, OrangeSlime,
	Wraith, Zombie,
	None
};

enum class eMidBossTypes
{
	DireBat, GrayDireBat,
	Minotaur, GrayMinotaur,
	GreenDragon, RedDragon, BlueDragon,
	Nightmare, BloodNightmare,
	Banshee, GreenBanshee,
	Mommy, Ogre,
	None
};

enum class BossTypes
{
	KingConga,
	DeathMetal,
	DeepBlues,
	CoralRiff,
	None
};
enum class eWallTypes
{
	DirtWall,
	StoneWall,
	CatacombWall,
	BossWall,
	GoldWall,
	HorizontalDoor,
	VerticalDoor,
	Border,
	None
};

enum class eFloorTypes
{
	Ground,
	Flash,
	Water,
	ClosedStairs,
	OpenedStairs,
	None
};