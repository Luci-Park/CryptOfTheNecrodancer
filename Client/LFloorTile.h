#pragma once
#include "LuciEngine.h"
#include "LSprite.h"
namespace cl
{
	class FloorTile
	{
#pragma region StaticInfo
	public:
		enum class eFloorTypes
		{
			Lobby,
			Ground,
			Flash,
			Water,
			Stairs
		};
		enum class eSpriteCategories {
			DarkFloor,
			LightFloor,
			GreenFlash,
			RedFlash,
			Water,
			ClosedStairs,
			OpenedStairs,
			Size
		};
		static Sprite GetFloorSprite(eSpriteCategories type);
	protected:
		enum class eSpriteTypes
			{
				DarkFloor1,
				DarkFloor2,
				DarkFloor3,
				DarkFloor4,
				LightFloor1,
				LightFloor2,
				LightFloor3,
				LightFloor4,
				GreenFlashFloor1,
				GreenFlashFloor2,
				RedFlashFloor1,
				RedFlashFloor2,
				Water1,
				Water2,
				Water3,
				ClosedStairs,
				OpenedStairs,
				Size
			};
		static const Vector2 floorTileIndex[];
		static const Vector2 floorSpriteSize;

		static Sprite GetFloorTile(eSpriteTypes tileType);
#pragma endregion

	public:
		FloorTile(Vector2 index, eFloorTypes type);
		virtual ~FloorTile();
		void OnBeat();
		void OnInteract();
		Sprite GetSprite();
	private:
		eFloorTypes mType;
		FloorStrategy* mStrategy;
		Vector2 mIndex;

	};

	class FloorStrategy
	{
	public:
		FloorStrategy();
		virtual ~FloorStrategy();
		virtual Sprite GetSprite() = 0;
		virtual void Interact() = 0;
		virtual void OnBeat() = 0;
	};

	class LobbyStrategy : public FloorStrategy
	{
	public:
		LobbyStrategy(Vector2 index);
		virtual ~LobbyStrategy(){}
		Sprite GetSprite()
		{
			return mSprite;
		}
		virtual void Interact() {}
		virtual void OnBeat() {}
	private:
		Sprite mSprite;
	};

	class GroundStrategy : public FloorStrategy
	{
	public:
		GroundStrategy();
		virtual ~GroundStrategy();
		virtual Sprite GetSprite() = 0;
		virtual void Interact() = 0;
		virtual void OnBeat() = 0;
	};

	class FlashStrategy : public FloorStrategy
	{
	public:
		FlashStrategy();
		virtual ~FlashStrategy();
		virtual Sprite GetSprite() = 0;
		virtual void Interact() = 0;
		virtual void OnBeat() = 0;
	};

	class WaterStrategy : public FloorStrategy
	{
	public:
		WaterStrategy();
		virtual ~WaterStrategy();
		virtual Sprite GetSprite() = 0;
		virtual void Interact() = 0;
		virtual void OnBeat() = 0;
	};

	class StairStrategy : public FloorStrategy
	{
	public:
		StairStrategy();
		virtual ~StairStrategy();
		virtual Sprite GetSprite() = 0;
		virtual void Interact() = 0;
		virtual void OnBeat() = 0;
	};
}

