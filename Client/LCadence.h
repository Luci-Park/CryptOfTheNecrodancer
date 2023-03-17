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
		Cadence(Scene* scene);
		~Cadence();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


		void Move();
	private:
		Animator* mAnimator;
		CadenceHead* mHead;
		CadenceBody* mBody;
	};

}

