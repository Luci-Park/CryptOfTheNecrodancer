#pragma once
#include "LGameObject.h"
#include "LSprite.h"
namespace cl
{
	class SpriteRenderer;
	class HeartUI : public GameObject
	{
	public:
		enum class State {Full, Half, Empty};
		HeartUI(Scene* sc);
		virtual ~HeartUI();

		virtual void SetHeart(State state);
	protected:
		SpriteRenderer* mSpriteRenderer;
		Sprite mFull;
		Sprite mHalf;
		Sprite mEmpty;
	};

	class HeartContainerUI : public HeartUI
	{
	public:
		HeartContainerUI(Scene* sc);
		virtual ~HeartContainerUI();
	};
	class CursedHeartUI : public HeartUI
	{
	public:
		CursedHeartUI(Scene* sc);
		virtual ~CursedHeartUI();

		virtual void SetHeart(State state) override;
	};
}

