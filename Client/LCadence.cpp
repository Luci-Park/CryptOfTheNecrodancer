#include "LCadence.h"
#include "LCadenceSprite.h"
#include "LObject.h"
#include "LInput.h"
#include "LTime.h"
#include "LSpriteRenderer.h"
#include "LCadenceAttackEffect.h"
namespace cl
{
	Cadence::Cadence(Scene* scene)
		: GameCharacter(scene)
		, mSpriteRenderer(nullptr)
		, mAttactEffect(nullptr)
	{
	}
	Cadence::~Cadence()
	{
	}
	void Cadence::Initialize()
	{
		GameCharacter::Initialize();
		mTransform->SetScale(Vector2::One * GameManager::UnitScale());
		
		mSpriteRenderer = AddComponent<SpriteRenderer>();
		mSpriteRenderer->SetImage(L"shadow", L"..\\Assets\\Arts\\Player\\Player_Shadow.bmp");
		mSpriteRenderer->AddAlpha(100);
		
		mSprite = object::Instantiate<CadenceSprite>(GameObject::GetScene(), GameObject::mTransform, GameObject::mTransform->GetPos(), eLayerType::Player);
		mAttactEffect = object::Instantiate<CadenceAttackEffect>(GameObject::GetScene(), GameObject::mTransform, GameObject::mTransform->GetPos(), eLayerType::Effects);
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
			mMoveTarget.x -= GameManager::UnitLength();
			mSprite->Turn(Vector2::Left);
			mSprite->Jump();
		}

		if (Input::GetKeyDown(eKeyCode::D))
		{
			mMoveTarget.x += GameManager::UnitLength();
			mSprite->Turn(Vector2::Right);
			mSprite->Jump();
		}

		if (Input::GetKeyDown(eKeyCode::W))
		{
			mMoveTarget.y -= GameManager::UnitLength();
			mSprite->Jump();
		}
		if (Input::GetKeyDown(eKeyCode::S))
		{
			mMoveTarget.y += GameManager::UnitLength();
			mSprite->Jump();
		}
		if (Input::GetKeyDown(eKeyCode::Q))
		{
			mAttactEffect->Attack(Vector2::Up);
		}

		if (Input::GetKeyDown(eKeyCode::E))
		{
			mAttactEffect->Attack(Vector2::Down);
		}

		if (Input::GetKeyDown(eKeyCode::R))
		{
			mSprite->Turn(Vector2::Left);
			mAttactEffect->Attack(Vector2::Left);
		}

		if (Input::GetKeyDown(eKeyCode::T))
		{
			mSprite->Turn(Vector2::Right);
			mAttactEffect->Attack(Vector2::Right);
		}
	}
	void Cadence::OnBeat()
	{
	}
	void Cadence::OnBeatChanged()
	{
		mAttactEffect->OnBeatChanged();
		GameCharacter::OnBeatChanged();
	}
}