#pragma once
#include "LuciEngine.h"
#include "LTileObject.h"
#include "LSprite.h"
namespace cl
{
	class SpriteRenderer;
	class AudioClip;
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
			Door,
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
		virtual void Dig(TileObject* object) override{}
		virtual void Attack(TileObject* object, Vector2 target)override{}
		virtual void OnDestroy();

		bool OnDig(int digPower);
		Vector2 GetPlateCenter();
		eWallTypes GetWallType() { return mWallType; }
	protected:
		SpriteRenderer* mSpriteRenderer;
		int mHardness;
		Sprite mWallSprite;
		eWallTypes mWallType;
		AudioClip* mDigClip;
		AudioClip* mDigFailedClip;
	};

	class GoldWall : public WallTile
	{
	public:
		GoldWall(Scene* sc);
		~GoldWall(){}
		virtual void OnDestroy() override;
	};
	class DirtWall : public WallTile
	{
	public:
		DirtWall(Scene* sc);
		~DirtWall() {}
		virtual void OnDestroy() override;
	};

}

