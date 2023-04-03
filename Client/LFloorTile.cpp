#include "LFloorTile.h"
#include "LSpriteRenderer.h"
#include "LResources.h"
#include "LObject.h"
#include "LMapManager.h"
namespace cl
{
#pragma region FloorTileStatic
	const Vector2 FloorTile::floorTileIndex[(int)(eSpriteTypes::Size)] = {
		Vector2(0, 0), // DarkFloor1
		Vector2(3, 0), // DarkFloor2
		Vector2(0, 1), // DarkFloor3
		Vector2(3, 1), // DarkFloor4
		Vector2(1, 0), // LightFloor1
		Vector2(2, 0), // LightFloor2
		Vector2(4, 0), // LightFloor3
		Vector2(5, 0), // LightFloor4
		Vector2(1, 1), // GreenFlashFloor1
		Vector2(4, 1), // GreenFlashFloor2
		Vector2(2, 1), // RedFlashFloor1
		Vector2(5, 1), // ReadFlashFloor2
		Vector2(6, 4), // Water1
		Vector2(7, 4), // Water2
		Vector2(8, 4), // Water3
		Vector2(8, 2),// ClosedStairs
		Vector2(6, 2)// OpenedStairs
	};
	const Vector2 FloorTile::floorSpriteSize = Vector2(26.0f, 26.0f);

	Sprite FloorTile::GetFloorTile(eSpriteTypes tileType)
	{
		Sprite sprite;
		Vector2 index = floorTileIndex[(int)tileType];
		sprite.leftTop.x = index.x * floorSpriteSize.x + 1;
		sprite.leftTop.y = index.y * floorSpriteSize.y + 1;
		sprite.size = Vector2(24.0f, 24.0f);
		sprite.offset -= sprite.size * 0.5;
		return sprite;
	}
	Sprite FloorTile::GetFloorSprite(eSpriteCategories type)
	{
		UINT min, max;
		switch (type)
		{
		case eSpriteCategories::DarkFloor:
			min = (UINT)eSpriteTypes::DarkFloor1;
			max = (UINT)eSpriteTypes::DarkFloor4;
			break;
		case eSpriteCategories::LightFloor:
			min = (UINT)eSpriteTypes::LightFloor1;
			max = (UINT)eSpriteTypes::LightFloor4;
			break;
		case eSpriteCategories::GreenFlash:
			min = (UINT)eSpriteTypes::GreenFlashFloor1;
			max = (UINT)eSpriteTypes::GreenFlashFloor2;
			break;
		case eSpriteCategories::RedFlash:
			min = (UINT)eSpriteTypes::RedFlashFloor1;
			max = (UINT)eSpriteTypes::RedFlashFloor2;
			break;
		case eSpriteCategories::Water:
			min = (UINT)eSpriteTypes::Water1;
			max = (UINT)eSpriteTypes::Water3;
			break;
		case eSpriteCategories::ClosedStairs:
			return GetFloorTile(eSpriteTypes::ClosedStairs);
		case eSpriteCategories::OpenedStairs:
			return GetFloorTile(eSpriteTypes::OpenedStairs);
			break;
		}
		int randomNumber = GetRandomInt(min, max);
		return GetFloorTile((eSpriteTypes)randomNumber);
	}
	FloorTile* FloorTile::CreateFloor(eFloorTypes type, Vector2 index, Scene* sc)
	{
		FloorTile* reslt = nullptr;
		Vector2 pos = index * UNITLENGTH;
		switch (type)
		{
		case eFloorTypes::Ground:
			reslt = object::Instantiate<GroundTile>(sc, pos, eLayerType::Background);
			reslt->SetFloorType(eFloorTypes::Ground);
			break;
		case eFloorTypes::Water:
			reslt = object::Instantiate<GroundTile>(sc, pos, eLayerType::Background);
			reslt->SetFloorType(eFloorTypes::Water);
			break;
		case eFloorTypes::ClosedStairs:
			reslt = object::Instantiate<StairTile>(sc, pos, eLayerType::Background);
			dynamic_cast<StairTile*>(reslt)->SetLock(true);
			break;
		case eFloorTypes::OpenedStairs:
			reslt = object::Instantiate<StairTile>(sc, pos, eLayerType::Background);
			dynamic_cast<StairTile*>(reslt)->SetLock(false);
			break;
		default:
			return nullptr;
		}
		reslt->SetIndex(index);
		return reslt;
	}
#pragma endregion

#pragma region Parent - FloorTile
	FloorTile::FloorTile(Scene* sc)
		:GameObject(sc, false) {
		mTransform->SetScale(Vector2::One * UNITSCALE);
	}

	FloorTile::~FloorTile(){
	}

	void FloorTile::Initialize()
	{
		mSpriteRenderer = AddComponent<SpriteRenderer>();
		mSpriteRenderer->SetImage(Resources::Load<Image>(L"Floors", L"..\\Assets\\Arts\\Stage Elements\\Floors.bmp"));
		GameObject::Initialize();
	}

	void FloorTile::Update()
	{
		Sprite newSprite = GetSprite();
		if (mSpriteRenderer->GetSprite() != newSprite)
		{
			mSpriteRenderer->SetSprite(newSprite);
		}

		GameObject::Update();
	}

	void FloorTile::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void FloorTile::OnInteract(TileObject* object)
	{
		if(mCurrStrategy != nullptr)
			mCurrStrategy->OnInteract(object);
	}

	Sprite FloorTile::GetSprite()
	{
		if (mCurrStrategy != nullptr)
			return mCurrStrategy->GetSprite();
	}
#pragma endregion

#pragma region Child - Ground Tile
	GroundTile::GroundTile(Scene* sc)
		:FloorTile(sc)
	{
	}
	GroundTile::~GroundTile()
	{
		for (int i = 0; i < (int)eFloorTypes::None; ++i)
		{
			if (mStrategy[i] != nullptr)
			{
				delete mStrategy[i];
				mStrategy[i] = nullptr;
			}
		}
	}
	void GroundTile::Update()
	{
		mCurrStrategy = mStrategy[(int)mType];
		FloorTile::Update();
	}
	void GroundTile::SetIndex(Vector2 index)
	{
		mIndex = index;
		mStrategy[(int)eFloorTypes::Ground] = new GroundStrategy(this);
		mStrategy[(int)eFloorTypes::Flash] = new FlashStrategy(this);
		mStrategy[(int)eFloorTypes::Water] = new WaterStrategy(this);

		mCurrStrategy = mStrategy[(int)mType];
	}
	void GroundTile::OnBeat()
	{
		mStrategy[(int)eFloorTypes::Ground]->OnBeat();
		mStrategy[(int)eFloorTypes::Flash]->OnBeat();
		mStrategy[(int)eFloorTypes::Water]->OnBeat();
	}
#pragma endregion
}