#include "LWallTile.h"
#include "LSpriteRenderer.h"
#include "LResources.h"
#include "LObject.h"
#include "LMapManager.h"
#include "LAudioClip.h"
#include "LDoor.h"
#include "LWallShadow.h"
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
		Vector2(16, 0),//DirtWallCrumble,
		Vector2(29, 0),//StoneWall,
		Vector2(30, 0), //StoneWallCrumble,
		Vector2(31, 0),//CatacombWall1,
		Vector2(32, 0),//CatacombWall2,
		Vector2(33, 0), //CatacombWallCrumble
		Vector2(34, 0),//BossWall1,
		Vector2(35, 0),//BossWall2,
		Vector2(36, 0),//BossWall3,
		Vector2(37, 0),//BossWall4,
		Vector2(38, 0),//BossWall5,
		Vector2(0, 6),//GoldWall,
		Vector2(1, 6),//GoldWallCrumble
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
		Vector2 pos = index * UNITLENGTH;
		switch (type)
		{
		case eWallTypes::DirtWall:
			reslt = object::Instantiate<DirtWall>(sc, pos, eLayerType::Wall);
			break;
		case eWallTypes::StoneWall:
			reslt = object::Instantiate<StoneWall>(sc, pos, eLayerType::Wall);
			break;

		case eWallTypes::CatacombWall:
			reslt = object::Instantiate<CatacombWall>(sc, pos, eLayerType::Wall);
			break;
		case eWallTypes::BossWall:
			reslt = object::Instantiate<BossWall>(sc, pos, eLayerType::Wall);
			break;
		case eWallTypes::GoldWall:
			reslt = object::Instantiate<GoldWall>(sc, pos, eLayerType::Wall);
			break;
		case eWallTypes::HorizontalDoor:
			reslt = object::Instantiate<Door>(sc, pos, eLayerType::Wall);
			((Door*)reslt)->SetHorizontal(true);
			break;
		case eWallTypes::VerticalDoor:
			reslt = object::Instantiate<Door>(sc, pos, eLayerType::Wall);
			((Door*)reslt)->SetHorizontal(false);
			break;
		case eWallTypes::Border:
			reslt = object::Instantiate<Border>(sc, pos, eLayerType::Wall);
			break;
		default:
			return nullptr;
		}
		reslt->SetIndex(index);
		return reslt;
	}

	Sprite WallTile::GetWallSprite(eWallTypes type)
	{
		UINT min, max;
		switch (type)
		{
		case eWallTypes::DirtWall:
			min = (UINT)eWallSpriteTypes::DirtWall1;
			max = (UINT)eWallSpriteTypes::DirtWall16;
			break;
		case eWallTypes::StoneWall:
			return GetWallSprite(eWallSpriteTypes::StoneWall);
			break;

		case eWallTypes::CatacombWall:
			min = (UINT)eWallSpriteTypes::CatacombWall1;
			max = (UINT)eWallSpriteTypes::CatacombWall2;
			break;

		case eWallTypes::BossWall:
			min = (UINT)eWallSpriteTypes::BossWall1;
			max = (UINT)eWallSpriteTypes::BossWall5;
			break;

		case eWallTypes::GoldWall:
			return GetWallSprite(eWallSpriteTypes::GoldWall);
			break;
		case eWallTypes::Border:
			min = (UINT)eWallSpriteTypes::Border1;
			max = (UINT)eWallSpriteTypes::Border8;
			break;
		case eWallTypes::HorizontalDoor:
			return GetWallSprite(eWallSpriteTypes::HorizontalDoor);
		case eWallTypes::VerticalDoor:
			return GetWallSprite(eWallSpriteTypes::VerticalDoor);
		}
		int randomNumber = GetRandomInt(min, max);
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
		:GameObject(sc, false)
		, mSpriteRenderer(nullptr)
		, mbIsBreakable(true)
	{
		mTransform->SetScale(Vector2::One * UNITSCALE);
		
	}

	void WallTile::Initialize()
	{
		mSpriteRenderer = AddComponent<SpriteRenderer>();
		mSpriteRenderer->SetImage(Resources::Load<Image>(L"Walls", L"..\\Assets\\Arts\\Stage Elements\\Walls.bmp"));
		mSpriteRenderer->SetSprite(mWallSprite);
		GameObject::Initialize();
		mShadow = object::Instantiate<WallShadow>(GameObject::GetScene(), mTransform, mTransform->GetPos(), eLayerType::Wall);
	}
	void WallTile::OnDestroy()
	{
		MapManager::DestroyWallObject(mIndex);
	}

	bool WallTile::OnCrumble()
	{
		mSpriteRenderer->SetSprite(mCrumbleSprite);
		mDigClip->Play(false);
		if (--mHardness <= 0)
		{
			OnDestroy();
		}
		return true;
	}

	bool WallTile::OnDig(int digPower)
	{
		if (digPower >= mHardness)
		{
			mDigClip->Play(false);
			OnDestroy();
			return true;
		}
		return false;
	}
	void WallTile::SetIndex(Vector2 index)
	{
		mShadow->SetIndex(index);
		mIndex = index;
	}
	Vector2 WallTile::GetPlateCenter()
	{
		Vector2 pos = mTransform->GetPos();
		pos.y -= 15 * UNITSCALE;
		return pos;
	}
#pragma endregion

#pragma region Dirt Wall
	DirtWall::DirtWall(Scene* sc)
		:WallTile(sc)
	{
		mHardness = 1;
		mWallSprite = WallTile::GetWallSprite(eWallTypes::DirtWall);
		mCrumbleSprite = WallTile::GetWallSprite(eWallSpriteTypes::DirtWallCrumble);
		mWallType = eWallTypes::DirtWall;
		mDigClip = Resources::Load<AudioClip>(L"DirtDig", L"..\\Assets\\Audio\\SoundEffects\\Walls\\mov_dig_dirt.wav");
	}
#pragma endregion

#pragma region Stone Wall
	StoneWall::StoneWall(Scene* sc)
		:WallTile(sc)
	{
		mHardness = 2;
		mWallSprite = WallTile::GetWallSprite(eWallTypes::StoneWall);
		mCrumbleSprite = WallTile::GetWallSprite(eWallSpriteTypes::StoneWallCrumble);
		mWallType = eWallTypes::StoneWall;
		mDigClip = Resources::Load<AudioClip>(L"StoneDig", L"..\\Assets\\Audio\\SoundEffects\\Walls\\mov_dig_stone.wav");
	}
#pragma endregion

#pragma region Catacomb Wall

	CatacombWall::CatacombWall(Scene* sc)
		:WallTile(sc)
	{
		mHardness = 3;
		mWallSprite = WallTile::GetWallSprite(eWallTypes::CatacombWall);
		mCrumbleSprite = WallTile::GetWallSprite(eWallSpriteTypes::CatacombWallCrumble);
		mWallType = eWallTypes::CatacombWall;
		mDigClip = Resources::Load<AudioClip>(L"StoneDig", L"..\\Assets\\Audio\\SoundEffects\\Walls\\mov_dig_brick.wav");
	}
#pragma endregion

#pragma region Boss Wall
	BossWall::BossWall(Scene* sc)
		:WallTile(sc)
	{
		mbIsBreakable = false;
		mWallSprite = WallTile::GetWallSprite(eWallTypes::BossWall);
	}

	bool BossWall::OnDig(int digPower)
	{
		return false;		
	}
	bool BossWall::OnCrumble()
	{
		return false;
	}
#pragma endregion

#pragma region Gold Wall
	GoldWall::GoldWall(Scene* sc)
		:WallTile(sc)
	{
		mHardness = 4;
		mWallSprite = WallTile::GetWallSprite(eWallTypes::GoldWall);
		mCrumbleSprite = WallTile::GetWallSprite(eWallSpriteTypes::GoldWallCrumble);
		mWallType = eWallTypes::GoldWall;
		mDigClip = Resources::Load<AudioClip>(L"BrickDig", L"..\\Assets\\Audio\\SoundEffects\\Walls\\mov_dig_brick.wav");
	}
	bool GoldWall::OnCrumble()
	{
		return false;
	}
	void GoldWall::OnDestroy()
	{
		WallTile::OnDestroy();
	}
#pragma endregion

#pragma region Border
	Border::Border(Scene* sc)
		:WallTile(sc)
	{
		mbIsBreakable = false;
		mHardness = 100;
		mWallSprite = WallTile::GetWallSprite(eWallTypes::BossWall);
	}

	bool Border::OnDig(int digPower)
	{
		return false;
	}
	bool Border::OnCrumble()
	{
		return false;
	}
#pragma endregion





}