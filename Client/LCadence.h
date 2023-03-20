#pragma once
#include "LGameCharacter.h"
namespace cl
{
	class SpriteRenderer;
	class Cadence : public GameCharacter
	{
	public:
		Cadence(Scene* scene);
		~Cadence();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void Move() override;
	private:
		SpriteRenderer* mSpriteRenderer;
	};

}

