#pragma once
#include "LGameObject.h"
namespace cl
{
	class Animator;
	class CadenceBody : public GameObject
	{
	public:
		CadenceBody(Scene* scene);
		~CadenceBody();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;
	private:
		Animator* mAnimator;
	};

}

