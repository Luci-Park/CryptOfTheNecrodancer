#include "LShovel.h"
#include "LWallTile.h"
#include "LAudioClip.h"
#include "LResources.h"
#include "LSpriteRenderer.h"
namespace cl
{
	//Sprite Shovel::shovelSprites[(int)eShovelTypes::Size] =
	//{
	//	//Sprite(Vector2 lefttop, Vector2 size, Vector2 offset)
	//	{Vector2(0, 3), Vector2(24, 24), Vector2(-12, -12)},
	//	{Vector2(29, 3), Vector2(24, 24), Vector2(-12, -12)},
	//	{Vector2(58, 3), Vector2(24, 24), Vector2(-12, -12)},
	//	{Vector2(87, 2), Vector2(24, 24), Vector2(-12, -12)},
	//	{Vector2(112, 1), Vector2(26, 26), Vector2(-13, -13)},
	//	{Vector2(138, 1), Vector2(26, 26), Vector2(-13, -13)},
	//	{Vector2(169, 3), Vector2(24, 24), Vector2(-12, -12)},
	//	{Vector2(198, 3), Vector2(24, 24), Vector2(-12, -12)},
	//	{Vector2(227, 6), Vector2(9, 18), Vector2(-5, -9)},
	//	{Vector2(241, 3), Vector2(23, 24), Vector2(-12, -12)}
	//};
	//Sprite Tool::GetShovelSprite(eShovelTypes type, bool isShadow)
	//{
	//	Sprite sprite = shovelSprites[(int)type];
	//	return sprite;
	//}

	Tool::Tool(Scene* sc)
		:Item(sc, eItemTypes::Tool)
	{
		mGetItemClip = Resources::Load<AudioClip>(L"sfx_pickup_weapon"
			, L"..\\Assets\\Audio\\SoundEffects\\SFX\\sfx_pickup_general_ST.wav");
		mDigFailedClip = Resources::Load<AudioClip>(L"DigFailed", L"..\\Assets\\Audio\\SoundEffects\\Walls\\mov_dig_fail.wav");
	}

	void Tool::Initialize()
	{
		mSpriteRenderer = AddComponent<SpriteRenderer>();
		mSpriteRenderer->SetImage(L"Shovels", L"..\\Assets\\Arts\\Items\\Shovels.bmp");
		SetSprite();
		Item::Initialize();
	}

	bool Tool::Dig(WallTile* object)
	{
		if (object != nullptr)
		{
			bool success = object->OnDig(mDigPower);
			if (!success)
				mDigFailedClip->Play(false);
		}
		return false;
	}


	Shovel::Shovel(Scene* sc)
		:Tool(sc)
	{
		mDigPower = 1;
	}
	Shovel::~Shovel()
	{
	}
	void Shovel::SetSprite()
	{  
		mSpriteRenderer->SetSprite({ Vector2(0, 3), Vector2(24, 24), Vector2(-12, -12) });
	}

	PickAxe::PickAxe(Scene* sc)
		:Tool(sc)
	{
	}
	PickAxe::~PickAxe()
	{
	}
	bool PickAxe::Dig(WallTile* object)
	{
		if (object != nullptr)
			return object->OnCrumble();
	}
	void PickAxe::SetSprite()
	{
		mSpriteRenderer->SetSprite({ Vector2(241, 3), Vector2(23, 24), Vector2(-12, -12) });
	}
}