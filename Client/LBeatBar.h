#pragma once
#include "LGameObject.h"
namespace cl
{
	class SpriteRenderer;
	class BeatBar : public GameObject
	{
	public:
		BeatBar(Scene* sc);
		~BeatBar();
	private:
		SpriteRenderer* mSpriteRenderer;
	};
}

