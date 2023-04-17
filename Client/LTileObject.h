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
		virtual void OnAttacked(float attackPower, Vector2 dir) = 0;
		virtual bool TryMove() = 0;
		virtual void OnDestroy() = 0;
		void SetIndex(Vector2 index) { mIndex = index; }
		void CalLightBrightness();
	protected:
		virtual void SetBrightness() = 0;
	protected:
		Vector2 mIndex;
	private:
		float CalLightBrightness(Vector2 tilePos, Vector2 lightPos, float innerRadius, float outerRadius);
		float innerRadius;
		float outerRadius;
	};
}
