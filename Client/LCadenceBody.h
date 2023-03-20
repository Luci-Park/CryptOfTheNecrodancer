#pragma once
#include "LGameObject.h"
#include "LBodyItem.h"
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

		void Flip(Vector2 dir) { mDir = dir; }
		void Reset();
		void SetDuration(float dur);
	private:
		void PlayRight();
		void PlayLeft();
	private:
		Animator* mAnimator;
		static const std::wstring mLeftAnimation;
		static const std::wstring mRightAnimation;
		static const int bodyIndex[];
		Vector2 mDir;
		
	};

}
