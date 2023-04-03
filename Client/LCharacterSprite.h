#pragma once
#include "LGameObject.h"
namespace cl
{
	class BeatManager;
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
		void Reset();
	protected:
		bool mbIsJumping;
		bool mbDirIsUp;
		float mHeight;

	};
}
