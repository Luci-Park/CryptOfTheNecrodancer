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
	Cadence::Cadence(Scene* scene)
		: GameCharacter(scene, false)
		, mSpriteRenderer(nullptr)
		, mAttackEffect(nullptr)
	{
		Camera::SetTarget(this);
		shovel = new PickAxe();
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
			if (mInput != Vector2::One)
			{
				SetSprite();
				if (!UnSink())
					OnMove(mInput);
				BeatManager::OnPlayerMove();
			}

		}
	}
	void Cadence::Render(HDC hdc)
	{
		GameCharacter::Render(hdc);
	}

	void Cadence::OnAttacked(int attackPower)
	{
	}
	void Cadence::OnDestroy()
	{
	}
	
	void Cadence::OnBeat()
	{
	}
	void Cadence::OnBeatChanged()
	{
		mAttackEffect->OnBeatChanged();
		GameCharacter::OnBeatChanged();
	}

	bool Cadence::TryAttack(Vector2 direction)
	{
		return false;
	}
	bool Cadence::TryDig(Vector2 direction)
	{
		WallTile* wall = MapManager::GetWall(mIndex + direction);
		if (wall && shovel)
		{
			mShovelEffect->OnDig(wall, shovel);
			bool success = shovel->Dig(wall);
			if (success)
			{
				PlayDigClip();
				Camera::StartShake();
			}
			return success;
		}
		return false;
	}
	bool Cadence::TryMove(Vector2 direction)
	{
		Vector2 dest = mIndex + direction;
		MapManager::Move(mIndex, dest);
		mSprite->Jump();
		mIndex = dest;
		mMoveTarget += direction * UNITLENGTH;
		return true;
	}
	
	void Cadence::GetInput()
	{
		mInput = Vector2::One;
		if (Input::GetKeyDown(eKeyCode::A))
		{
			mInput = Vector2::Left;
		}

		if (Input::GetKeyDown(eKeyCode::D))
		{
			mInput = Vector2::Right;
		}

		if (Input::GetKeyDown(eKeyCode::W))
		{
			mInput = Vector2::Up;
		}

		if (Input::GetKeyDown(eKeyCode::S))
		{
			mInput = Vector2::Down;
		}
	}
	void Cadence::SetSprite()
	{
		if (mInput != Vector2::One)
		{
			mShovelEffect->Reset();
			mSprite->Turn(mInput);
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



}