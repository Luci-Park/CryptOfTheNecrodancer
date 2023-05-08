#pragma once
#include "LGameObject.h"
#include "LSprite.h"
namespace cl
{
	class SpriteRenderer;
	class BeatBar : public GameObject
	{
	public:
		BeatBar(Scene* sc);
		~BeatBar();
		void SetToUrgent();
	private:
		SpriteRenderer* mSpriteRenderer;
		Sprite mNormalBeat;
		Sprite mUrgentBeat;
	};
}

