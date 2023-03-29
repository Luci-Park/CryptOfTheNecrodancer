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

		void Jump();
	protected:
		bool mbIsJumping;
		bool mbDirIsUp;
		float mHeight;

	};
}
