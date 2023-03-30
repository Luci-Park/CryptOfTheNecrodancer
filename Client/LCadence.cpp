#include "LCadence.h"
#include "LCadenceSprite.h"
#include "LCadenceAttackEffect.h"
#include "LMapManager.h"
#include "LObject.h"
#include "LCamera.h"
#include "LInput.h"
#include "LTime.h"
#include "LSpriteRenderer.h"
#include "LWallTile.h"
namespace cl
{
	int Cadence::_attackPower = 1;
	int Cadence::_digPower = 1;
	int Cadence::_health = 3;
	int Cadence::_heartCount = 3;

	void Cadence::Reset()
	{
		_attackPower = 1;
		_digPower = 1;
		_health = 3;
		_heartCount = 3;
	}
	Cadence::Cadence(Scene* scene)
		: GameCharacter(scene)
		, mSpriteRenderer(nullptr)
		, mAttackEffect(nullptr)
	{
	}
	Cadence::~Cadence()
	{
		Camera::SetTarget(nullptr);
	}
	void Cadence::Initialize()
	{
		GameCharacter::Initialize();
		mTransform->SetScale(Vector2::One * MapManager::UnitScale());
		
		//mSpriteRenderer = AddComponent<SpriteRenderer>();
		//mSpriteRenderer->SetImage(L"shadow", L"..\\Assets\\Arts\\Player\\Player_Shadow.bmp");
		//mSpriteRenderer->AddAlpha(100);
		
		mSprite = object::Instantiate<CadenceSprite>(GameObject::GetScene(), GameObject::mTransform, GameObject::mTransform->GetPos(), eLayerType::Foreground);
		mAttackEffect = object::Instantiate<CadenceAttackEffect>(GameObject::GetScene(), GameObject::mTransform, GameObject::mTransform->GetPos(), eLayerType::Effects);

		//Camera::SetTarget(this);
	}
	void Cadence::Update()
	{
		GameCharacter::Update();
	}
	void Cadence::Render(HDC hdc)
	{
		GameCharacter::Render(hdc);
	}
	void Cadence::Move()
	{
		if (Input::GetKeyDown(eKeyCode::A))
		{
			mSprite->Turn(Vector2::Left);
			Vector2 dest = mIndex;
			dest.x -= 1;
			bool success = !MapManager::OnInteractObject(this, mIndex, dest);
			if (success)
			{
				mMoveTarget.x -= MapManager::UnitLength();
				mSprite->Jump();
				mIndex.x -= 1;
			}
		}

		if (Input::GetKeyDown(eKeyCode::D))
		{
			mSprite->Turn(Vector2::Right);
			Vector2 dest = mIndex;
			dest.x += 1;
			bool success = !MapManager::OnInteractObject(this, mIndex, dest);
			if (success)
			{
				mMoveTarget.x += MapManager::UnitLength();
				mSprite->Jump();
				mIndex.x += 1;
			}
		}

		if (Input::GetKeyDown(eKeyCode::W))
		{
			Vector2 dest = mIndex;
			dest.y -= 1;
			bool success = !MapManager::OnInteractObject(this, mIndex, dest);
			if (success)
			{
				mMoveTarget.y -= MapManager::UnitLength();
				mSprite->Jump();
				mIndex.y -= 1;
			}
		}
		if (Input::GetKeyDown(eKeyCode::S))
		{
			Vector2 dest = mIndex;
			dest.y += 1;
			bool success = !MapManager::OnInteractObject(this, mIndex, dest);
			if (success)
			{
				mMoveTarget.y += MapManager::UnitLength();
				mSprite->Jump();
				mIndex.y += 1;
			}
		}
		if (Input::GetKeyDown(eKeyCode::Q))
		{
			Camera::StartShake();
			mAttackEffect->Attack(Vector2::Up);
		}

		if (Input::GetKeyDown(eKeyCode::E))
		{
			Camera::StartShake();
			mAttackEffect->Attack(Vector2::Down);
		}

		if (Input::GetKeyDown(eKeyCode::R))
		{
			Camera::StartShake();
			mSprite->Turn(Vector2::Left);
			mAttackEffect->Attack(Vector2::Left);
		}

		if (Input::GetKeyDown(eKeyCode::T))
		{
			Camera::StartShake();
			mSprite->Turn(Vector2::Right);
			mAttackEffect->Attack(Vector2::Right);
		}
	}
	void Cadence::OnBeat()
	{
	}
	void Cadence::OnBeatChanged()
	{
		mAttackEffect->OnBeatChanged();
		GameCharacter::OnBeatChanged();
	}
	void Cadence::Interact(TileObject* object)
	{
		if (object != nullptr)
			object->Attack(this);
	}
	void Cadence::Dig(TileObject* object)
	{
		WallTile* tile = dynamic_cast<WallTile*>(object);
		if (tile != nullptr)
		{
			tile->OnDig(mDigPower);
		}
	}
	void Cadence::Attack(TileObject* object)
	{
	}
}