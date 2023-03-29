#include "LWallTile.h"
#include "LSpriteRenderer.h"
#include "LResources.h"
#include "LGameManager.h"
#include "LObject.h"
#include "LMapManager.h"
namespace cl
{
#pragma region Static Info
	const Vector2 WallTile::wallSpriteSize = Vector2(24.0f, 48.0f);
	const Vector2 WallTile::wallTileIndex[(int)WallTile::eWallSpriteTypes::Size] = {

		Vector2(0, 0),//DirtWall1,
		Vector2(1, 0),//DirtWall2,
		Vector2(2, 0),//DirtWall3,
		Vector2(3, 0),//DirtWall4,
		Vector2(4, 0),//DirtWall5,
		Vector2(5, 0),//DirtWall6,
		Vector2(6, 0),//DirtWall7,
		Vector2(7, 0),//DirtWall8,
		Vector2(8, 0),//DirtWall9,
		Vector2(9, 0),//DirtWall10,
		Vector2(10, 0),//DirtWall11,
		Vector2(11, 0),//DirtWall12,
		Vector2(12, 0),//DirtWall13,
		Vector2(13, 0),//DirtWall14,
		Vector2(14, 0),//DirtWall15,
		Vector2(15, 0),//DirtWall16,
		Vector2(29, 0),//HarderWall,
		Vector2(31, 0),//StoneWall1,
		Vector2(32, 0),//StoneWall2,
		Vector2(34, 0),//BossWall1,
		Vector2(35, 0),//BossWall2,
		Vector2(36, 0),//BossWall3,
		Vector2(37, 0),//BossWall4,
		Vector2(38, 0),//BossWall5,
		Vector2(0, 6),//GoldWall,
		Vector2(4, 6),//Border1,
		Vector2(5, 6),//Border2,
		Vector2(6, 6),//Border3,
		Vector2(7, 6),//Border4,
		Vector2(8, 6),//Border5,
		Vector2(9, 6),//Border6,
		Vector2(10, 6),//Border7,
		Vector2(11, 6),//Border8,
		Vector2(12, 6),//DoorHorizontal,
		Vector2(13, 6),//DoorVertical,
	};

	WallTile* WallTile::CreateWall(eWallTypes type, Vector2 index, Scene* sc)
	{
		WallTile* reslt = nullptr;
		Vector2 pos = Vector2(index.x * GameManager::UnitLength(), index.y * GameManager::UnitLength());
		switch (type)
		{
		case eWallTypes::GoldWall:
			reslt = object::Instantiate<GoldTile>(sc, pos, eLayerType::Wall);
			break;
		default:
			return nullptr;
		}
		reslt->SetIndex(index);
		return nullptr;
	}

	Sprite WallTile::GetWallSprite(eWallTypes type)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		UINT min, max;
		switch (type)
		{
		case eWallTypes::DirtWall:
			min = (UINT)eWallSpriteTypes::DirtWall1;
			max = (UINT)eWallSpriteTypes::DirtWall16;
			break;
		case eWallTypes::HardWall:
			return GetWallSprite(eWallSpriteTypes::HarderWall);
			break;

		case eWallTypes::StoneWall:
			min = (UINT)eWallSpriteTypes::StoneWall1;
			max = (UINT)eWallSpriteTypes::StoneWall2;
			break;

		case eWallTypes::BossWall:
			min = (UINT)eWallSpriteTypes::BossWall1;
			max = (UINT)eWallSpriteTypes::BossWall5;
			break;

		case eWallTypes::GoldWall:
			return GetWallSprite(eWallSpriteTypes::GoldWall);
			break;

		case eWallTypes::DoorHorizontal:
			return GetWallSprite(eWallSpriteTypes::DoorHorizontal);
			break;

		case eWallTypes::DoorVertical:
			return GetWallSprite(eWallSpriteTypes::DoorVertical);
			break;

		case eWallTypes::Border:
			min = (UINT)eWallSpriteTypes::Border1;
			max = (UINT)eWallSpriteTypes::Border8;
			break;
		}
		std::uniform_int_distribution<> distrib(min, max);
		int randomNumber = distrib(gen);
		return GetWallSprite((eWallSpriteTypes)randomNumber);
	}

	Sprite WallTile::GetWallSprite(eWallSpriteTypes type)
	{
		Sprite sprite;
		Vector2 index = wallTileIndex[(int)type];
		sprite.leftTop.x = index.x * wallSpriteSize.x;
		sprite.leftTop.y = index.y * wallSpriteSize.y;
		sprite.size = Vector2(24.0f, 39.0f);
		sprite.offset = Vector2(-12.0f, -27.0f);
		return sprite;
	}
#pragma endregion

#pragma region Parent - Wall Tile
	WallTile::WallTile(Scene* sc)
		:TileObject(sc)
		,mSpriteRenderer(nullptr)
	{
		mTransform->SetScale(Vector2::One * GameManager::UnitScale());
	}

	void WallTile::Initialize()
	{
		mSpriteRenderer = AddComponent<SpriteRenderer>();
		mSpriteRenderer->SetImage(Resources::Load<Image>(L"Walls", L"..\\Assets\\Arts\\Stage Elements\\Walls.bmp"));
		mSpriteRenderer->SetSprite(mWallSprite);
		TileObject::Initialize();
	}

	void WallTile::Interact(TileObject* object)
	{
		object->Dig(this);
	}
	void WallTile::OnDestroy()
	{
		MapManager::DestroyObject(mIndex);
	}
#pragma endregion

#pragma region GoldTile
	GoldTile::GoldTile(Scene* sc)
		:WallTile(sc)
	{
		mHardness = 4;
		mWallSprite = WallTile::GetWallSprite(eWallTypes::GoldWall);
	}
	void GoldTile::OnDestroy()
	{
		WallTile::OnDestroy();
	}
#pragma endregion


}