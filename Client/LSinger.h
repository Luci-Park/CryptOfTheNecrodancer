#pragma once
#include "LGameObject.h"
namespace cl
{
	class Singer : public GameObject
	{
	public:
		enum class eSingingState
		{
			Idle,
			Up,
			Down,
			Left,
			Right,
			Size
		};
		Singer();
		virtual ~Singer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void ChangeState(eSingingState state);
	protected:
		eSingingState mCurrState;
		virtual void OnIdle() = 0;
		virtual void OnUp() = 0;
		virtual void OnDown() = 0;
		virtual void OnLeft() = 0;
		virtual void OnRight() = 0;
	};
}

