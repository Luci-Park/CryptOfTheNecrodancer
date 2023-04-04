#pragma once
#include "LGameObject.h"
#include "LMath.h"
namespace cl
{
	class WallTile;
	class TileObject : public GameObject
	{
	public:
		TileObject(Scene* sc);
		virtual ~TileObject(){}
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void Sink() = 0;

		virtual void OnAttacked(int attackPower) = 0;
		virtual void OnDestroy() = 0;

		void SetIndex(Vector2 index) { mIndex = index; }
	protected:
		Vector2 mIndex;
	};
}
