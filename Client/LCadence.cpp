#include "LCadence.h"
#include "LCadenceHead.h"
#include "LCadenceBody.h"
#include "LObject.h"
#include "LInput.h"
#include "LTime.h"
namespace cl
{
	Cadence::Cadence(Scene* scene)
		:GameObject(scene, false)
	{
	}
	Cadence::~Cadence()
	{
	}
	void Cadence::Initialize()
	{
		mTransform->SetScale(Vector2(2.5f, 2.5f));
		mBody = object::Instantiate<CadenceBody>(GameObject::GetScene(), GameObject::mTransform, GameObject::mTransform->GetPos(), eLayerType::Player);
		mHead = object::Instantiate<CadenceHead>(GameObject::GetScene(), GameObject::mTransform, GameObject::mTransform->GetPos(), eLayerType::Player);
		mePlayerState = IDLE;
		moveTowardsPosition = mTransform->GetPos();
	}
	void Cadence::Update()
	{
		Vector2 reslt = Vector2::MoveTowards(mTransform->GetPos(), moveTowardsPosition, mMoveSpeed * Time::DeltaTime());
		mTransform->SetPos(reslt);
		if (Vector2::Distance(mTransform->GetPos(), moveTowardsPosition) <= 0.001f)
		{
			if (Input::GetKeyDown(eKeyCode::A))
			{
				moveTowardsPosition.x -= mMoveLength;
				mBody->Flip(false);
				mHead->Flip(false);
				mbMoving = true;
			}

			if (Input::GetKeyDown(eKeyCode::D))
			{
				moveTowardsPosition.x += mMoveLength;
				mBody->Flip(true);
				mHead->Flip(true);
				mbMoving = true;
			}

			if (Input::GetKeyDown(eKeyCode::W))
			{
				moveTowardsPosition.y -= mMoveLength;
				mbMoving = true;
			}
			if (Input::GetKeyDown(eKeyCode::S))
			{
				moveTowardsPosition.y += mMoveLength;
				mbMoving = true;
			}
		}
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
	}
	void Cadence::Release()
	{
	}
	void Cadence::Move()
	{
		Vector2 pos = mTransform->GetPos();
		float tile = 100.0f;
		if (Input::GetKeyDown(eKeyCode::A))
		{
			pos.x -= 100.0f;
			mBody->Flip(false);
			mHead->Flip(false);
		}

		if (Input::GetKeyDown(eKeyCode::D))
		{
			pos.x += 100.0f;
			mBody->Flip(true);
			mHead->Flip(true);
		}

		if (Input::GetKeyDown(eKeyCode::W))
			pos.y -= 100.0f;
		if (Input::GetKeyDown(eKeyCode::S))
			pos.y += 100.0f;

		mTransform->SetPos(pos);
	}
}