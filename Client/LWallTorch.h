#include "LTileObject.h"
#pragma once
namespace cl
{
	class Animator;
	class LightSource;
	class WallTorch : public TileObject
	{
	public:
		WallTorch(Scene* sc);
		virtual ~WallTorch();

		virtual void Initialize() override;

		virtual void Update()override;
		virtual void Render(HDC hdc) override;
		virtual void Sink(){}
		virtual bool OnAttacked(float attackPower, Vector2 dir);
		virtual bool TryMove() { return false; }

	private:
		Animator* mAnimator;
		LightSource* mLightSource;
	};
}

