#pragma once
#include "LuciEngine.h"
#include "LSprite.h"
#include "LGameObject.h"
namespace cl
{
	class SpriteRenderer;
	class FloorStrategy;
	class FloorTile : public GameObject
	{
#pragma region StaticInfo
	public:
		enum class eFloorTypes
		{
			Lobby,
			Ground,
			Water,
			ClosedStairs,
			OpenedStairs,
			None
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
		static FloorTile* CreateFloor(eFloorTypes type, Vector2 index, Scene* sc);
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
		FloorTile(Scene* sc);
		virtual ~FloorTile();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		
		virtual void SetIndex(Vector2 index) = 0;
		Vector2 GetIndex() { return mIndex; }
		virtual void OnBeat();
		virtual void OnInteract();

	protected:
		Sprite GetSprite();
		FloorStrategy* mStrategy;
		SpriteRenderer* mSpriteRenderer;
		eFloorTypes mType;
		Vector2 mIndex;
	};

	class LobbyTile : public FloorTile
	{
	public:
		LobbyTile(Scene* sc);
		virtual ~LobbyTile();

		virtual void SetIndex(Vector2 index);
	};

	class GroundTile : public FloorTile
	{
	public:
		GroundTile(Scene* sc);
		virtual ~GroundTile();

		virtual void SetIndex(Vector2 index);

	};

	class WaterTile : public FloorTile
	{
	public:
		WaterTile(Scene* sc);
		virtual ~WaterTile();
		virtual void SetIndex(Vector2 index);
	};

	class StairTile : public FloorTile
	{
	public:
		StairTile(Scene* sc);
		virtual ~StairTile();
		virtual void SetIndex(Vector2 index);
		virtual void OnBeat(){}
		virtual void OnInteract();
		void SetDestination(eSceneType type) { mMoveScene = type; }
		void SetLock(bool isLocked) { mIsLocked = isLocked; }
		bool IsLocked() { return mIsLocked; }
	private:
		eSceneType mMoveScene;
		bool mIsLocked;
	};
}

