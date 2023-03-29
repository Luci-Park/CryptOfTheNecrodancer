#include "LFloorStrategy.h"
#include "LFloorTile.h"
namespace cl
{
#pragma region Parent - FloorStrategy
	FloorStrategy::FloorStrategy(FloorTile* tile)
	{
		mTile = tile;
		Vector2 index = tile->GetIndex();
		if (((int)index.y % 2 == 0 && (int)index.x % 2 == 0) || ((int)index.y % 2 == 1 && (int)index.x % 2 == 1))
			mIsEven = true;
		else
			mIsEven = false;
	}
#pragma endregion

#pragma region Child - Lobby Strategy
	LobbyStrategy::LobbyStrategy(FloorTile* tile)
		:FloorStrategy(tile)
	{
		if (mIsEven)
			mSprite = FloorTile::GetFloorSprite(FloorTile::eSpriteCategories::LightFloor);
		else
			mSprite = FloorTile::GetFloorSprite(FloorTile::eSpriteCategories::DarkFloor);
	}
#pragma endregion

#pragma region Child - Stair Strategy
	StairStrategy::StairStrategy(StairTile* tile)
		:FloorStrategy(tile)
	{
		mOpenSprite = FloorTile::GetFloorSprite(FloorTile::eSpriteCategories::OpenedStairs);
		mClosedSprite = FloorTile::GetFloorSprite(FloorTile::eSpriteCategories::ClosedStairs);
		if (tile->IsLocked())
			mCurrSprite = mClosedSprite;
		else
			mCurrSprite = mOpenSprite;
		mStairTile = tile;
	}
	StairStrategy::~StairStrategy()
	{
	}
	Sprite StairStrategy::GetSprite()
	{
		return mCurrSprite;
	}
	void StairStrategy::OnBeat()
	{
		if (mCurrSprite == mClosedSprite && !mStairTile->IsLocked())
			mCurrSprite = mOpenSprite;
	}
#pragma endregion
}