#include "LCadence.h"
#include "LCadenceSprite.h"
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
#include "LDagger.h"
#include "LWeapon.h"
namespace cl
{
	Cadence::Cadence(Scene* scene)
		: GameCharacter(scene, true)
		, mSpriteRenderer(nullptr)
	{
		//Camera::SetTarget(this);
		mShovel = new Shovel();
		SetDigClip();
	}
	Cadence::~Cadence()
	{
		delete mShovel; mShovel = nullptr;
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
		mWeapon = object::Instantiate<Dagger>(GameObject::GetScene(), GameObject::mTransform, GameObject::mTransform->GetPos(), eLayerType::Effects);
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

	void Cadence::OnAttacked(float attackPower)
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
		mWeapon->OnBeatChanged();
		GameCharacter::OnBeatChanged();
	}

	void Cadence::OnMove(Vector2 direction)
	{
		if (!TryAttack(direction) && !TryDig(direction))
			TryMove(direction);
	}

	bool Cadence::TryAttack(Vector2 direction)
	{
		return mWeapon->Attack(mIndex, direction);
	}

	bool Cadence::TryDig(Vector2 direction)
	{
		WallTile* wall = MapManager::GetWall(mIndex + direction);
		if (wall)
		{
			if (mShovel)
			{
				mShovelEffect->OnDig(wall, mShovel);
				bool success = mShovel->Dig(wall);
				if (success)
				{
					PlayDigClip();
					Camera::StartShake();
				}
			}
			return true;//I tried dig
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
	void Cadence::SetAttackClip()
	{

	}
	void Cadence::PlayAttackClip()
	{

	}

}