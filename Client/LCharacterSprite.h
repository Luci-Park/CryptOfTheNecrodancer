#pragma once
#include "LGameObject.h"
namespace cl
{
	class BeatManager;
	class Animator;
	class CharacterSprite : public GameObject
	{
	public :
		CharacterSprite(Scene* sc);
		virtual ~CharacterSprite();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc)override;

		virtual void Turn(Vector2 dir) = 0;
		virtual void OnBeatChanged() = 0;

		virtual void Jump();
		virtual void Sink();
		virtual void UnSink();
		//virtual void Flash() = 0;

		void Reset();
		void MoveFailed(Vector2 dir);
	protected:
		bool mbIsJumping;
		bool mbDirIsUp;
		
		bool mbMoveFailed;
		Vector2 mbMoveDir;
		float mHeight;
		Animator* mAnimator;

	};
}
