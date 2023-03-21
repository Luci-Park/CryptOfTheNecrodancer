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
	Effects,
	UI,
	Size = 16,
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