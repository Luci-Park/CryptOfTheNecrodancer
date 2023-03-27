#pragma once
#include "LSprite.h"
namespace cl
{
	class FloorTile;
	class FloorStrategy
	{
	public:
		FloorStrategy(FloorTile* tile);
		virtual ~FloorStrategy(){}
		virtual Sprite GetSprite() = 0;
		virtual void Interact() = 0;
		virtual void OnBeat() = 0;
	protected:
		FloorTile* mTile;
		bool mIsLightTile;
	};

	class LobbyStrategy : public FloorStrategy
	{
	public:
		LobbyStrategy(FloorTile* tile);
		virtual ~LobbyStrategy() {}
		Sprite GetSprite(){return mSprite;}
		virtual void Interact() {}
		virtual void OnBeat() {}
	private:
		Sprite mSprite;
	};

	class GroundStrategy : public FloorStrategy
	{
	public:
		GroundStrategy(FloorTile* tile);
		virtual ~GroundStrategy();
		virtual Sprite GetSprite() = 0;
		virtual void Interact() = 0;
		virtual void OnBeat() = 0;
	};

	class FlashStrategy : public FloorStrategy
	{
	public:
		FlashStrategy(FloorTile* tile);
		virtual ~FlashStrategy();
		virtual Sprite GetSprite() = 0;
		virtual void Interact() = 0;
		virtual void OnBeat() = 0;
	};

	class WaterStrategy : public FloorStrategy
	{
	public:
		WaterStrategy(FloorTile* tile);
		virtual ~WaterStrategy();
		virtual Sprite GetSprite() = 0;
		virtual void Interact() = 0;
		virtual void OnBeat() = 0;
	};

	class StairStrategy : public FloorStrategy
	{
	public:
		StairStrategy(FloorTile* tile);
		virtual ~StairStrategy();
		virtual Sprite GetSprite() = 0;
		virtual void Interact() = 0;
		virtual void OnBeat() = 0;
	};
}

