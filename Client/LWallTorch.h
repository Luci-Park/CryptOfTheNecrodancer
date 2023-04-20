#include "LTileObject.h"
#pragma once
namespace cl
{
	class Animator;
	class WallTorch : public TileObject
	{
	public:
		WallTorch(Scene* sc);
		virtual ~WallTorch(){}

		virtual void Initialize() override;

		virtual void Update()override;
		virtual void Render(HDC hdc) override;
		virtual void Sink(){}
		virtual void OnAttacked(float attackPower, Vector2 dir);
		virtual bool TryMove() { return false; }
		virtual void OnDestroy();

	protected:
		virtual void SetBrightness() override;

	private:
		Animator* mAnimator;
	};
}
