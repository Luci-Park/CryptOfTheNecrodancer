#pragma once
#include "LGameObject.h"
namespace cl
{
	class Animator;
	class CadenceHead;
	class CadenceBody;
	class Cadence : public GameObject
	{
	public:
		enum PlayerState
		{IDLE, Moving, Attacking};
		Cadence(Scene* scene);
		~Cadence();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void Move();
	private:
		float mMoveSpeed = 100.0f;
		bool mbMoving = false;
		float mMoveLength = 100.0f;
		PlayerState mePlayerState;
		Vector2 moveTowardsPosition;
		Animator* mAnimator;
		CadenceHead* mHead;
		CadenceBody* mBody;
	};

}

