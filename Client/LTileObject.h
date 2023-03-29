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

		virtual void Interact(TileObject* tile) = 0;
		virtual void Dig(TileObject* tile) = 0;
		virtual void Attack(TileObject* tile) = 0;

		void SetIndex(Vector2 index) { mIndex = index; }
	protected:
		int mDigPower;
		int mAttackPower;
		int mDefense;
		Vector2 mIndex;
	};
}
