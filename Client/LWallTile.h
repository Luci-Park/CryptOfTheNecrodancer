#pragma once
#include "LuciEngine.h"
#include "LTileObject.h"
#include "LSprite.h"
namespace cl
{
	class SpriteRenderer;
	class WallTile : public TileObject
	{
#pragma region Static Info
	public:
		enum class eWallTypes
		{
			DirtWall,
			HardWall,
			StoneWall,
			BossWall,
			GoldWall,
			DoorHorizontal,
			DoorVertical,
			Border,
			None
		};
		
		static WallTile* CreateWall(eWallTypes type, Vector2 index, Scene* sc);
	protected:
		enum class eWallSpriteTypes
			{
				DirtWall1,
				DirtWall2,
				DirtWall3,
				DirtWall4,
				DirtWall5,
				DirtWall6,
				DirtWall7,
				DirtWall8,
				DirtWall9,
				DirtWall10,
				DirtWall11,
				DirtWall12,
				DirtWall13,
				DirtWall14,
				DirtWall15,
				DirtWall16,
				HarderWall,
				StoneWall1,
				StoneWall2,
				BossWall1,
				BossWall2,
				BossWall3,
				BossWall4,
				BossWall5,
				GoldWall,
				Border1,
				Border2,
				Border3,
				Border4,
				Border5,
				Border6,
				Border7,
				Border8,
				DoorHorizontal,
				DoorVertical,
				Size
			};

		static Sprite GetWallSprite(eWallTypes type);
		static const Vector2 wallTileIndex[];
		static const Vector2 wallSpriteSize;

	private:
		static Sprite GetWallSprite(eWallSpriteTypes type);
#pragma endregion

	public:
		WallTile(Scene* sc);
		virtual ~WallTile(){}

		virtual void Initialize();

		virtual void Interact(TileObject* object) override;
		virtual void Dig(TileObject* object){}
		virtual void Attack(TileObject* object){}
		virtual void OnDestroy();

		int GetHardness() { return mHardness; }
	protected:
		SpriteRenderer* mSpriteRenderer;
		int mHardness;
		Sprite mWallSprite;
	};

	class GoldTile : public WallTile
	{
	public:
		GoldTile(Scene* sc);
		~GoldTile(){}
		virtual void OnDestroy() override;
	};

}

