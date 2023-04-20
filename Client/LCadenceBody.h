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

		void Flip(Vector2 dir);
		void Reset();
		void SetDuration(float dur);
		void Sink();
		void UnSink();
		void Flash();
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
