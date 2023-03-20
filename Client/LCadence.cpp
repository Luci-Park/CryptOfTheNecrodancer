#include "LCadence.h"
#include "LCadenceSprite.h"
#include "LObject.h"
#include "LInput.h"
#include "LTime.h"
namespace cl
{
	Cadence::Cadence(Scene* scene)
		:GameCharacter(scene)
	{
	}
	Cadence::~Cadence()
	{
	}
	void Cadence::Initialize()
	{
		mTransform->SetScale(Vector2(2.5f, 2.5f));
		mSprite = object::Instantiate<CadenceSprite>(GameObject::GetScene(), GameObject::mTransform, GameObject::mTransform->GetPos(), eLayerType::Player);
		mSprite->SetManager(mGameManager);
		GameCharacter::Initialize();
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
		}

		if (Input::GetKeyDown(eKeyCode::D))
		{
			mMoveTarget.x += mGameManager->Displacement();
			mSprite->Turn(Vector2::Right);
		}

		if (Input::GetKeyDown(eKeyCode::W))
			mMoveTarget.y -= mGameManager->Displacement();
		if (Input::GetKeyDown(eKeyCode::S))
			mMoveTarget.y += mGameManager->Displacement();
	}
}