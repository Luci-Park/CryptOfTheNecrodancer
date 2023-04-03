#include "LCadence.h"
#include "LCadenceSprite.h"
#include "LCadenceAttackEffect.h"
#include "LCadenceShovelEffect.h"
#include "LMapManager.h"
#include "LBeatManager.h"
#include "LObject.h"
#include "LCamera.h"
#include "LInput.h"
#include "LTime.h"
#include "LSpriteRenderer.h"
#include "LWallTile.h"
#include "LShovel.h"
#include "LResources.h"
#include "LAudioClip.h"
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
		Camera::SetTarget(this);
		shovel = new Shovel();
		SetDigClip();
	}
	Cadence::~Cadence()
	{
		delete shovel; shovel = nullptr;

		Camera::SetTarget(nullptr);
	}
	void Cadence::Initialize()
	{
		GameCharacter::Initialize();
		mTransform->SetScale(Vector2::One * UNITSCALE);
		
		//mSpriteRenderer = AddComponent<SpriteRenderer>();
		//mSpriteRenderer->SetImage(L"shadow", L"..\\Assets\\Arts\\Player\\Player_Shadow.bmp");
		//mSpriteRenderer->AddAlpha(100);
		
		mSprite = object::Instantiate<CadenceSprite>(GameObject::GetScene(), GameObject::mTransform, GameObject::mTransform->GetPos(), eLayerType::Player);
		mAttackEffect = object::Instantiate<CadenceAttackEffect>(GameObject::GetScene(), GameObject::mTransform, GameObject::mTransform->GetPos(), eLayerType::Effects);
		mShovelEffect = object::Instantiate<CadenceShovelEffect>(GameObject::GetScene(), GameObject::mTransform, GameObject::mTransform->GetPos(), eLayerType::Effects);
	}
	void Cadence::Update()
	{
		GameCharacter::Update();
		if (!mbIsMoving)
		{
			GetInput();
			if (mInput != PlayerInput::None)
			{
				SetSprite();
				if (!UnSink())
					Move();
				BeatManager::OnPlayerMove();
			}

		}
	}
	void Cadence::Render(HDC hdc)
	{
		GameCharacter::Render(hdc);
	}
	void Cadence::GetInput()
	{
		mInput = PlayerInput::None;
		if (Input::GetKeyDown(eKeyCode::A))
		{
			mInput = PlayerInput::Left;
		}

		if (Input::GetKeyDown(eKeyCode::D))
		{
			mInput = PlayerInput::Right;
		}

		if (Input::GetKeyDown(eKeyCode::W))
		{
			mInput = PlayerInput::Up;
		}

		if (Input::GetKeyDown(eKeyCode::S))
		{
			mInput = PlayerInput::Down;
		}
	}
	void Cadence::SetSprite()
	{
		if (mInput != PlayerInput::None)
		{
			mShovelEffect->Reset();
			if (mInput == PlayerInput::Left)
				mSprite->Turn(Vector2::Left);
			else if(mInput == PlayerInput::Right)
				mSprite->Turn(Vector2::Right);
		}
	}
	void Cadence::Move()
	{
		if (Input::GetKeyDown(eKeyCode::A))
		{
			Vector2 dest = mIndex;
			dest.x -= 1;
			bool success = !MapManager::OnInteractObject(this, mIndex, dest);
			if (success)
			{
				mMoveTarget.x -= UNITLENGTH;
				mSprite->Jump();
				mIndex.x -= 1;
			}
		}

		if (Input::GetKeyDown(eKeyCode::D))
		{
			Vector2 dest = mIndex;
			dest.x += 1;
			bool success = !MapManager::OnInteractObject(this, mIndex, dest);
			if (success)
			{
				mMoveTarget.x += UNITLENGTH;
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
				mMoveTarget.y -= UNITLENGTH;
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
				mMoveTarget.y += UNITLENGTH;
				mSprite->Jump();
				mIndex.y += 1;
			}
		}
	}
	bool Cadence::UnSink()
	{
		if (mbIsSinked)
		{
			mbIsSinked = false;
			mSprite->UnSink();
			return true;
		}
			return false;
	}
	void Cadence::SetDigClip()
	{
		std::wstring key = L"dig_0";
		std::wstring path = L"..\\Assets\\Audio\\SoundEffects\\Cadence\\Dig\\vo_cad_";

		for (int i = 0; i < 6; ++i)
		{
			std::wstring newKey = key + std::to_wstring(i + 1);
			std::wstring newPath = path + newKey + L".wav";
			mDigClip[i] = Resources::Load<AudioClip>(newKey, newPath);
		}
	}
	void Cadence::PlayDigClip()
	{
		int random = GetRandomInt(0, 5);
		mDigClip[random]->SetVolume(25.f);
		mDigClip[random]->Play(false);
	}
	void Cadence::OnBeat()
	{
	}
	void Cadence::OnBeatChanged()
	{
		mAttackEffect->OnBeatChanged();
		GameCharacter::OnBeatChanged();
	}

	void Cadence::Dig(WallTile* object)
	{
		if (shovel != nullptr)
		{
			mShovelEffect->OnDig(object, shovel);
			bool success = shovel->Dig(object);
			if (success)
			{
				PlayDigClip();
				Camera::StartShake();
			}
		}
	}
	void Cadence::Attack(TileObject* object, Vector2 target)
	{
		Camera::StartShake();
		Vector2 pressedPos;
		if (mInput == PlayerInput::Up)
			pressedPos = Vector2::Up;
		else if (mInput == PlayerInput::Down)
			pressedPos = Vector2::Down;
		else if (mInput == PlayerInput::Left)
			pressedPos = Vector2::Left;
		else if (mInput == PlayerInput::Right)
			pressedPos = Vector2::Right;
		mAttackEffect->OnAttack(pressedPos);
	}
	void Cadence::OnDestroy()
	{
	}
	void Cadence::OnAttacked()
	{
	}
}