#pragma once
#include "LGameObject.h"
#include "LSpriteRenderer.h"
namespace cl
{
	class FloorShadow : public GameObject
	{
	public:
		FloorShadow(Scene* sc);
		virtual ~FloorShadow();

		virtual void Initialize();
		virtual void Update();

		void SetIndex(Vector2 index);
	private:
		SpriteRenderer* mShadow;
		Vector2 mIndex;
	};
}

