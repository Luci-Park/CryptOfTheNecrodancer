#pragma once
#include "LSprite.h"
#include "LAudioClip.h"
namespace cl
{
	class FloorTile;
	class StairTile;
	class TileObject;
	class FloorStrategy
	{
	public:
		FloorStrategy(FloorTile* tile);
		virtual ~FloorStrategy(){}
		virtual Sprite GetSprite() = 0;
		virtual void OnBeat() = 0;
		virtual void OnInteract(TileObject* object) = 0;
	protected:
		FloorTile* mTile;
		bool mIsEven;
	};

	class LobbyStrategy : public FloorStrategy
	{
	public:
		LobbyStrategy(FloorTile* tile);
		virtual ~LobbyStrategy() {}
		Sprite GetSprite(){return mSprite;}
		virtual void OnBeat() {}
	private:
		Sprite mSprite;
	};

	class GroundStrategy : public FloorStrategy
	{
	public:
		GroundStrategy(FloorTile* tile);
		virtual ~GroundStrategy(){}
		virtual Sprite GetSprite();
		virtual void OnBeat();
		virtual void OnInteract(TileObject* object){}
	private:
		Sprite mSprites[2];
		bool mIndex;
	};

	class FlashStrategy : public FloorStrategy
	{
	public:
		FlashStrategy(FloorTile* tile);
		virtual ~FlashStrategy(){}
		virtual Sprite GetSprite();
		virtual void OnBeat();
		virtual void OnInteract(TileObject* object) {}
	private:
		Sprite mSprites[2];
		bool mIndex;
	};

	class WaterStrategy : public FloorStrategy
	{
	public:
		WaterStrategy(FloorTile* tile);
		virtual ~WaterStrategy(){}
		virtual Sprite GetSprite() { return mSprite; }
		virtual void OnBeat();
		virtual void OnInteract(TileObject* object);
	private:
		Sprite mSprite;
		bool mbInteracted;
		AudioClip* mInWaterClip;
		AudioClip* mOutWaterClip;
	};

	class StairStrategy : public FloorStrategy
	{
	public:
		StairStrategy(StairTile* tile);
		virtual ~StairStrategy();
		virtual Sprite GetSprite();
		virtual void OnBeat();
		virtual void OnInteract(TileObject* object) {}
	private:
		Sprite mOpenSprite;
		Sprite mClosedSprite;
		Sprite mCurrSprite;
		StairTile* mStairTile;
	};
}

