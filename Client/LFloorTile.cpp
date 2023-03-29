#include "LFloorTile.h"
#include "LSpriteRenderer.h"
#include "LResources.h"
#include "LFloorStrategy.h"
#include "LObject.h"
#include "LGameManager.h"
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
		std::random_device rd;
		std::mt19937 gen(rd());
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
		std::uniform_int_distribution<> distrib(min, max);
		int randomNumber = distrib(gen);
		return GetFloorTile((eSpriteTypes)randomNumber);
	}
	FloorTile* FloorTile::CreateFloor(eFloorTypes type, Vector2 index, Scene* sc)
	{
		FloorTile* reslt = nullptr;
		Vector2 pos = Vector2(index.x * GameManager::UnitLength(), index.y * GameManager::UnitLength());
		switch (type)
		{
		case eFloorTypes::Lobby:
			reslt = object::Instantiate<LobbyTile>(sc, pos, eLayerType::Background);
			break;
		case eFloorTypes::Ground:
			reslt = object::Instantiate<GroundTile>(sc, pos, eLayerType::Background);
			break;
		case eFloorTypes::Water:
			reslt = object::Instantiate<WaterTile>(sc, pos, eLayerType::Background);
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
		mTransform->SetScale(Vector2::One * GameManager::UnitScale());
	}

	FloorTile::~FloorTile(){
		if (mStrategy != nullptr)
		{
			delete mStrategy;
			mStrategy = nullptr;
		}
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

	void FloorTile::OnBeat()
	{
		if (mStrategy != nullptr)
			mStrategy->OnBeat();
	}

	Sprite FloorTile::GetSprite()
	{
		if (mStrategy != nullptr)
			return mStrategy->GetSprite();
	}

	void FloorTile::OnInteract()
	{
	}
#pragma endregion

#pragma region Child - LobbyTile
	LobbyTile::LobbyTile(Scene* sc)
		:FloorTile(sc){}

	LobbyTile::~LobbyTile()
	{
	}
	void LobbyTile::SetIndex(Vector2 index)
	{
		mIndex = index;
		mStrategy = new LobbyStrategy(this);
	}
#pragma endregion

#pragma region Child - Ground Tile
	GroundTile::GroundTile(Scene* sc)
		:FloorTile(sc)
	{
	}
	GroundTile::~GroundTile()
	{
	}
	void GroundTile::SetIndex(Vector2 index)
	{
		mIndex = index;
	}
#pragma endregion

#pragma region Child - Water Tile
	WaterTile::WaterTile(Scene* sc)
		:FloorTile(sc)
	{
	}
	WaterTile::~WaterTile()
	{
	}
	void WaterTile::SetIndex(Vector2 index)
	{
		mIndex = index;
	}
#pragma endregion
}