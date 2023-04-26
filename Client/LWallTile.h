#pragma once
#include "LuciEngine.h"
#include "LTileObject.h"
#include "LSprite.h"
namespace cl
{
	class SpriteRenderer;
	class AudioClip;
	class WallShadow;
	class WallTile : public GameObject
	{
#pragma region Static Info
	public:		
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
				DirtWallCrumble,
				StoneWall,
				StoneWallCrumble,
				CatacombWall1,
				CatacombWall2,
				CatacombWallCrumble,
				BossWall1,
				BossWall2,
				BossWall3,
				BossWall4,
				BossWall5,
				GoldWall,
				GoldWallCrumble,
				Border1,
				Border2,
				Border3,
				Border4,
				Border5,
				Border6,
				Border7,
				Border8,
				HorizontalDoor,
				VerticalDoor,
				Size
			};

		static Sprite GetWallSprite(eWallSpriteTypes type);
		static Sprite GetWallSprite(eWallTypes type);
		static const Vector2 wallTileIndex[];
		static const Vector2 wallSpriteSize;

	private:
#pragma endregion

	public:
		WallTile(Scene* sc);
		virtual ~WallTile(){}

		virtual void Initialize() override;
		virtual void Render(HDC hdc) override;
		virtual bool OnDig(int digPower);
		virtual bool OnCrumble();
		virtual void OnDestroy();

		void SetIndex(Vector2 index);
		Vector2 GetPlateCenter();
		eWallTypes GetWallType() { return mWallType; }
		bool IsBreakable() { return mbIsBreakable; }
	protected:
		eWallTypes mWallType;
		int mHardness;
		Vector2 mIndex;

		SpriteRenderer* mSpriteRenderer;
		Sprite mWallSprite;
		Sprite mCrumbleSprite;
		AudioClip* mDigClip;
		AudioClip* mDigFailedClip;
		bool mbIsBreakable;
		WallShadow* mShadow;
	};

	class DirtWall : public WallTile
	{
	public:
		DirtWall(Scene* sc);
		~DirtWall() {}
	};

	class StoneWall : public WallTile
	{
	public:
		StoneWall(Scene* sc);
		~StoneWall() {}
	};

	class CatacombWall : public WallTile
	{
	public:
		CatacombWall(Scene* sc);
		~CatacombWall() {}
	};	

	class BossWall : public WallTile
	{
	public:
		BossWall(Scene* sc);
		~BossWall() {}
		virtual bool OnDig(int digPower) override;
		virtual bool OnCrumble() override;
	};

	class GoldWall : public WallTile
	{
	public:
		GoldWall(Scene* sc);
		~GoldWall() {}
		virtual bool OnCrumble() override;
		virtual void OnDestroy() override;
	};

	class Border : public WallTile
	{
	public:
		Border(Scene* sc);
		~Border() {}
		virtual bool OnDig(int digPower) override;
		virtual bool OnCrumble() override;
	};
}

