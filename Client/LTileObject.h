#pragma once
#include "LGameObject.h"
#include "LMath.h"
namespace cl
{
	class TileObject : public GameObject
	{
	public:
		TileObject(Scene* sc);
		virtual ~TileObject(){}
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void Sink() = 0;
		virtual bool OnAttacked(float attackPower, Vector2 dir) = 0;
		virtual bool TryMove() = 0;
		virtual void OnDestroy();

		void SetIndex(Vector2 index) { mIndex = index; }
	protected:
		Vector2 mIndex;
		float mInnerRadius;
		float mOuterRadius;
	};
}
