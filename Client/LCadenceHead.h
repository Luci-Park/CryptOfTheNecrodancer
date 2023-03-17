#pragma once
#include "LGameObject.h"
namespace cl
{
	class Animator;
	class CadenceHead : public GameObject
	{
	public:
		CadenceHead(Scene* scene);
		~CadenceHead();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;
	private:
		Animator* mAnimator;
	};

}

