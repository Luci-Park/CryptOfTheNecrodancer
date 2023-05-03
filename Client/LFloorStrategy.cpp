#include "LFloorStrategy.h"
#include "LFloorTile.h"
#include "LTileObject.h"
#include "LResources.h"
#include "LGrooveChain.h"
#include "LCadence.h"
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
	InactiveDirtStrategy::InactiveDirtStrategy(FloorTile* tile)
		:FloorStrategy(tile)
	{
		mSprite = FloorTile::GetFloorSprite(FloorTile::eSpriteCategories::LightFloor);
	}
#pragma endregion


	ActiveDirtStrategy::ActiveDirtStrategy(FloorTile* tile)
		:FloorStrategy(tile)
	{
		mSprites[0] = FloorTile::GetFloorSprite(FloorTile::eSpriteCategories::LightFloor);
		mSprites[1] = FloorTile::GetFloorSprite(FloorTile::eSpriteCategories::DarkFloor);
		mIndex = mIsEven;
		ChangeToFlash();
	}

	Sprite ActiveDirtStrategy::GetSprite()
	{
		return mSprites[mIndex];
	}

	void ActiveDirtStrategy::OnBeat()
	{
		mIndex = !mIndex;
		ChangeToFlash();
	}

	void ActiveDirtStrategy::ChangeToFlash()
	{
		if (mTile->GetFloorType() == eFloorTypes::ActiveDirt)
		{
			if (GrooveChainManager::GrooveChain() > MINGROOVE)
				mTile->SetFloorType(eFloorTypes::Flash);
		}
	}

	FlashStrategy::FlashStrategy(FloorTile* tile)
		:FloorStrategy(tile)
	{
		if (mIsEven)
			mSprites[0] = FloorTile::GetFloorSprite(FloorTile::eSpriteCategories::GreenFlash);
		else
			mSprites[0] = FloorTile::GetFloorSprite(FloorTile::eSpriteCategories::RedFlash);
		mSprites[1] = FloorTile::GetFloorSprite(FloorTile::eSpriteCategories::DarkFloor);
		mIndex = mIsEven;
		ChangeToDefault();
	}

	Sprite FlashStrategy::GetSprite()
	{
		return mSprites[mIndex];
	}

	void FlashStrategy::OnBeat()
	{
		mIndex = !mIndex;
		ChangeToDefault();
	}

	void FlashStrategy::ChangeToDefault()
	{
		if (mTile->GetFloorType() == eFloorTypes::Flash)
		{
			if (GrooveChainManager::GrooveChain() == MINGROOVE)
				mTile->SetFloorType(eFloorTypes::ActiveDirt);
		}
	}
	
	WaterStrategy::WaterStrategy(FloorTile* tile)
		:FloorStrategy(tile)
	{
		mSprite = FloorTile::GetFloorSprite(FloorTile::eSpriteCategories::Water);
		mInWaterClip = Resources::Load<AudioClip>(L"InWater", L"..\\Assets\\Audio\\SoundEffects\\Floor\\mov_water_in.wav");
		mOutWaterClip = Resources::Load<AudioClip>(L"OutWater", L"..\\Assets\\Audio\\SoundEffects\\Floor\\mov_water_out.wav");
	}
	void WaterStrategy::OnBeat()
	{
		if (mbInteracted)
		{
			mOutWaterClip->Play(false);
			mbInteracted = false;
			mTile->SetFloorType(eFloorTypes::ActiveDirt);
		}
	}
	void WaterStrategy::OnInteract(TileObject* object)
	{
		mInWaterClip->Play(false);
		object->Sink();
		mbInteracted = true;
	}
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

		mErrorSound = Resources::Load<AudioClip>(L"sfx_error_ST", L"..\\Assets\\Audio\\SoundEffects\\Floor\\sfx_error_ST.wav");
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
		mCurrSprite = mStairTile->IsLocked() ? mClosedSprite : mOpenSprite;
	}
	void StairStrategy::OnInteract(TileObject* object)
	{
		Cadence* c = dynamic_cast<Cadence*>(object);
		if (c != nullptr)
		{
			if (mStairTile->IsLocked())
				mErrorSound->Play(false);
			else
				mStairTile->LoadScene();
		}
	}
#pragma endregion
}