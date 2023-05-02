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
	Gold,
	Items,
	Player,
	Monster,
	Wall,
	Hearts,
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
	BlueBat, RedBat,
	WhiteSkeleton, YellowSkeleton, BlackSkeleton,
	BlueSlime, GreenSlime, OrangeSlime,
	Zombie,
	YellowDireBat, BrownDireBat,
	LightMinotaur, DarkMinotaur,
	GreenDragon, RedDragon,

	DeepBlues,
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
	InactiveDirt,
	ActiveDirt,
	Flash,
	Water,
	ClosedStairs,
	OpenedStairs,
	None
};

enum class eItemTypes
{
	Tool,
	Weapon,
	Armor,
	Headware,
	Footware,
	Torches,
	Rings,
	Consumables,
	Size
};