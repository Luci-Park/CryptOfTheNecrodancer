#include "LFloorTile.h"
namespace cl
{
	const Vector2 FloorTile::floorTileIndex[(int)(eSpriteTypes::Size)] = {
		Vector2(0, 0), // DarkFloor1
		Vector2(0, 3), // DarkFloor2
		Vector2(1, 0), // DarkFloor3
		Vector2(1, 3), // DarkFloor4
		Vector2(0, 1), // LightFloor1
		Vector2(0, 2), // LightFloor2
		Vector2(0, 4), // LightFloor3
		Vector2(0, 5), // LightFloor4
		Vector2(1, 1), // GreenFlashFloor1
		Vector2(1, 4), // GreenFlashFloor2
		Vector2(1, 2), // RedFlashFloor1
		Vector2(1, 5), // ReadFlashFloor2
		Vector2(4, 6), // Water1
		Vector2(4, 7), // Water2
		Vector2(4, 8), // Water3
		Vector2(2, 8),// ClosedStairs
		Vector2(2, 6)// OpenedStairs
	};
	const Vector2 FloorTile::floorSpriteSize = Vector2(27.0f, 27.0f);

	Sprite FloorTile::GetFloorTile(eSpriteTypes tileType)
	{
		Sprite sprite;
		Vector2 index = floorTileIndex[(int)tileType];
		sprite.leftTop.x = index.x * floorSpriteSize.x + 1;
		sprite.leftTop.y = index.y * floorSpriteSize.y + 1;
		sprite.size = Vector2(24.0f, 24.0f);
		sprite.offset -= sprite.size * 0.5;
		return sprite;
	}
	Sprite FloorTile::GetFloorSprite(eSpriteCategories type)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		UINT min, max;
		switch (type)
		{
		case eSpriteCategories::DarkFloor:
			min = (UINT)eSpriteTypes::DarkFloor1;
			max = (UINT)eSpriteTypes::DarkFloor4;
			break;
		case eSpriteCategories::LightFloor:
			min = (UINT)eSpriteTypes::LightFloor1;
			max = (UINT)eSpriteTypes::LightFloor4;
			break;
		case eSpriteCategories::GreenFlash:
			min = (UINT)eSpriteTypes::GreenFlashFloor1;
			max = (UINT)eSpriteTypes::GreenFlashFloor2;
			break;
		case eSpriteCategories::RedFlash:
			min = (UINT)eSpriteTypes::RedFlashFloor1;
			max = (UINT)eSpriteTypes::RedFlashFloor2;
			break;
		case eSpriteCategories::Water:
			min = (UINT)eSpriteTypes::Water1;
			max = (UINT)eSpriteTypes::Water3;
			break;
		case eSpriteCategories::ClosedStairs:
			return GetFloorTile(eSpriteTypes::ClosedStairs);
		case eSpriteCategories::OpenedStairs:
			return GetFloorTile(eSpriteTypes::OpenedStairs);
			break;
		}
		std::uniform_int_distribution<> distrib(min, max);
		int randomNumber = distrib(gen);
		return GetFloorTile((eSpriteTypes)randomNumber);
	}

	FloorTile::FloorTile(Vector2 index, eFloorTypes type)
	{
		mIndex = index;
		mType = type;
	}

	FloorTile::~FloorTile()
	{
	}

	void FloorTile::OnBeat()
	{
		if (mStrategy != nullptr)
			mStrategy->OnBeat();
	}

	Sprite FloorTile::GetSprite()
	{
		if (mStrategy != nullptr)
			mStrategy->GetSprite();
	}

	void FloorTile::OnInteract()
	{
		if (mStrategy != nullptr)
			mStrategy->Interact();
	}

	FloorStrategy::FloorStrategy()
	{
	}

	FloorStrategy::~FloorStrategy()
	{
	}

	LobbyStrategy::LobbyStrategy(Vector2 index)
	{
		int order = index.x + 1 + index.y + 1;
		mSprite = order % 2 ?
			FloorTile::GetFloorSprite(FloorTile::eSpriteCategories::DarkFloor) :
			FloorTile::GetFloorSprite(FloorTile::eSpriteCategories::LightFloor);
	}

}