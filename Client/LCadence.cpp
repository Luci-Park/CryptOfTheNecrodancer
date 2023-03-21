#include "LCadence.h"
#include "LCadenceSprite.h"
#include "LObject.h"
#include "LInput.h"
#include "LTime.h"
#include "LSpriteRenderer.h"
namespace cl
{
	Cadence::Cadence(Scene* scene)
		: GameCharacter(scene)
		, mSpriteRenderer(nullptr)
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
	}
	void Cadence::OnBeat()
	{
	}
}