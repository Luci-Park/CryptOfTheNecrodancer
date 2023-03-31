#include "LCadence.h"
#include "LCadenceSprite.h"
#include "LCadenceAttackEffect.h"
#include "LMapManager.h"
#include "LBeatManager.h"
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
		: GameCharacter(scene, false)
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
			pressedPos = Vector2::Left;
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
			BeatManager::OnPlayerMove();
		}

		if (Input::GetKeyDown(eKeyCode::D))
		{
			pressedPos = Vector2::Right;
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
			BeatManager::OnPlayerMove();
		}

		if (Input::GetKeyDown(eKeyCode::W))
		{
			pressedPos = Vector2::Up;
			Vector2 dest = mIndex;
			dest.y -= 1;
			bool success = !MapManager::OnInteractObject(this, mIndex, dest);
			if (success)
			{
				mMoveTarget.y -= MapManager::UnitLength();
				mSprite->Jump();
				mIndex.y -= 1;
			}
			BeatManager::OnPlayerMove();
		}
		if (Input::GetKeyDown(eKeyCode::S))
		{
			pressedPos = Vector2::Down;
			Vector2 dest = mIndex;
			dest.y += 1;
			bool success = !MapManager::OnInteractObject(this, mIndex, dest);
			if (success)
			{
				mMoveTarget.y += MapManager::UnitLength();
				mSprite->Jump();
				mIndex.y += 1;
			}
			BeatManager::OnPlayerMove();
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
			object->Attack(this, mIndex);
	}
	void Cadence::Dig(TileObject* object)
	{
		WallTile* tile = dynamic_cast<WallTile*>(object);
		if (tile != nullptr)
		{
			if (tile->OnDig(mDigPower))
			{
				Camera::StartShake();
			}
		}
	}
	void Cadence::Attack(TileObject* object, Vector2 target)
	{
		Camera::StartShake();
		mAttackEffect->Attack(pressedPos);
	}
}