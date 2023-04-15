#include "LDoor.h"
#include "LResources.h"
#include "LSpriteRenderer.h"
#include "LMapManager.h"
namespace cl
{
	Door::Door(Scene* sc)
		:WallTile(sc)
	{
		mHardness = 0;
		mDigClip = Resources::Load<AudioClip>(L"DoorOpen", L"..\\Assets\\Audio\\SoundEffects\\Walls\\obj_door_open.wav");
	}
	void Door::Update()
	{
		if (mbIsHorizontal)
		{
			if (MapManager::GetWall(mIndex + Vector2::Left) == nullptr
				&& MapManager::GetWall(mIndex + Vector2::Right) == nullptr)
				OnDig(0);
		}
		else
		{
			if (MapManager::GetWall(mIndex + Vector2::Up) == nullptr
				&& MapManager::GetWall(mIndex + Vector2::Down) == nullptr)
				OnDig(0);
		}
		GameObject::Update();
	}

	bool Door::OnDig(int digPower)
	{	
		if (mbIsHorizontal)
		{
			Door* door = dynamic_cast<Door*>(MapManager::GetWall(mIndex + Vector2::Left));
			if (door != nullptr) door->OnDig(digPower);
			door = dynamic_cast<Door*>(MapManager::GetWall(mIndex + Vector2::Right));
			if (door != nullptr) door->OnDig(digPower);
		}
		else
		{
			Door* door = dynamic_cast<Door*>(MapManager::GetWall(mIndex + Vector2::Up));
			if (door != nullptr) door->OnDig(digPower);
			door = dynamic_cast<Door*>(MapManager::GetWall(mIndex + Vector2::Down));
			if (door != nullptr) door->OnDig(digPower);
		}
		return WallTile::OnDig(digPower);
	}

	bool Door::OnCrumble()
	{
		return OnDig(1);
	}
	void Door::SetHorizontal(bool isHorizontal)
	{
		mbIsHorizontal = isHorizontal;
		mWallType = isHorizontal ? eWallTypes::HorizontalDoor : eWallTypes::VerticalDoor;
		mWallSprite = WallTile::GetWallSprite(mWallType);
		mSpriteRenderer->SetSprite(mWallSprite);
	}
}