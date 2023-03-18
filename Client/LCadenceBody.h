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

		void Flip(bool right) { isRight = right; }
	private:
		void PlayRight();
		void PlayLeft();
	private:
		Animator* mAnimator;
		static const std::wstring mLeftAnimation;
		static const std::wstring mRightAnimation;
		bool isRight = true;
		
	};

}

