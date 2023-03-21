#pragma once
#include "LGameCharacter.h"
namespace cl
{
	class SpriteRenderer;
	class CadenceAttackEffect;
	class Cadence : public GameCharacter
	{
	public:
		Cadence(Scene* scene);
		~Cadence();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void Move() override;
		virtual void OnBeat() override;
		virtual void OnBeatChanged() override;
	private:
		SpriteRenderer* mSpriteRenderer;
		CadenceAttackEffect* mAttactEffect;
	};

}

