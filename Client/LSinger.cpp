#include "LSinger.h"

namespace cl
{
	Singer::Singer()
		:GameObject(false)
	{
	}
	Singer::~Singer()
	{
	}
	void Singer::Initialize()
	{
		GameObject::Initialize();
	}
	void Singer::Update()
	{
		switch (mCurrState)
		{
		case eSingingState::Idle:
			OnIdle();
			break;
		case eSingingState::Up:
			OnUp();
			break;
		case eSingingState::Down:
			OnDown();
			break;
		case eSingingState::Left:
			OnLeft();
			break;
		case eSingingState::Right:
			OnRight();
			break;
		}
		GameObject::Update();
	}
	void Singer::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Singer::Release()
	{
		GameObject::Release();
	}
	void Singer::ChangeState(eSingingState state)
	{
		mCurrState = state;
	}
}