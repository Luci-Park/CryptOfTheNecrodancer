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
		virtual void OnBeatChanged();

		virtual void Jump();
		virtual void Sink();
		virtual void UnSink();
		virtual void Flash();
		virtual void SetShadow(bool inShadow) { mbInShadows = inShadow; }
		void Reset();
	protected:
		bool mbIsJumping;
		bool mbDirIsUp;
		
		bool mbIsFlashing;
		float mFlashTimer;
		float mFlashDuration;

		bool mbInShadows;

		bool mbMoveFailed;
		Vector2 mbMoveDir;
		float mHeight;
		Animator* mAnimator;

	};
}
