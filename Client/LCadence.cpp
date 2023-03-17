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
		mBody = object::Instantiate<CadenceBody>(GameObject::GetScene(), GameObject::mTransform, GameObject::mTransform->GetPos(), eLayerType::Player);
		mHead = object::Instantiate<CadenceHead>(GameObject::GetScene(), GameObject::mTransform, GameObject::mTransform->GetPos(), eLayerType::Player);
	}
	void Cadence::Update()
	{
		Move();
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
		if (Input::GetKey(eKeyCode::A))
			pos.x -= 100.0f * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::D))
			pos.x += 100.0f * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::W))
			pos.y -= 100.0f * Time::DeltaTime();
		if (Input::GetKey(eKeyCode::S))
			pos.y += 100.0f * Time::DeltaTime();

		mTransform->SetPos(pos);
	}
}