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
		mTransform->SetScale(Vector2(2.5f, 2.5f));
		mSpriteRenderer = AddComponent<SpriteRenderer>();/*
		mSpriteRenderer->SetImage(L"shadow", L"..\\Assets\\Arts\\shadow.bmp");
		mSpriteRenderer->SetOffset(Vector2::Down * 2.5f);*/
		mSprite = object::Instantiate<CadenceSprite>(GameObject::GetScene(), GameObject::mTransform, GameObject::mTransform->GetPos(), eLayerType::Player);
	}
	void Cadence::Update()
	{
		GameCharacter::Update();
	}
	void Cadence::Render(HDC hdc)
	{
		Vector2 pos = mTransform->GetPos();
		Vector2 width = Vector2(100, 100);
		HBRUSH newBrush = CreateSolidBrush(RGB(255, 0, 0));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, newBrush);
		Rectangle(hdc, pos.x - width.x * 0.5, pos.y - width.y * 0.5, pos.x + width.x * 0.5, pos.y + width.y * 0.5);
		SelectObject(hdc, oldBrush);
		DeleteObject(newBrush);
		GameCharacter::Render(hdc);
	}
	void Cadence::Release()
	{
		GameCharacter::Release();
	}
	void Cadence::Move()
	{
		if (Input::GetKeyDown(eKeyCode::A))
		{
			mMoveTarget.x -= mGameManager->Displacement();
			mSprite->Turn(Vector2::Left);
			mSprite->Jump();
		}

		if (Input::GetKeyDown(eKeyCode::D))
		{
			mMoveTarget.x += mGameManager->Displacement();
			mSprite->Turn(Vector2::Right);
			mSprite->Jump();
		}

		if (Input::GetKeyDown(eKeyCode::W))
		{
			mMoveTarget.y -= mGameManager->Displacement();
			mSprite->Jump();
		}
		if (Input::GetKeyDown(eKeyCode::S))
		{
			mMoveTarget.y += mGameManager->Displacement();
			mSprite->Jump();
		}
	}
}