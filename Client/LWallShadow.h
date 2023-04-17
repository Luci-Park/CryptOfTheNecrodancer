#pragma once
#include "LGameObject.h"
#include "LSpriteRenderer.h"
namespace cl
{
	class WallShadow : public GameObject
	{
	public:
		WallShadow(Scene* sc);
		virtual ~WallShadow();

		virtual void Initialize();
		virtual void Update();

		void SetIndex(Vector2 index);
	private:
		SpriteRenderer* mShadow;
		Vector2 mIndex;
	};
}

