#pragma once
#include "LGameCharacter.h"
namespace cl
{
	class Monster : public GameCharacter
	{
	public:
		Monster(Scene* sc, bool isFlying);
		virtual ~Monster();

		virtual void Initialize()override;

		virtual void OnBeat() override;
		virtual void OnBeatChanged()override;

		virtual void Dig(TileObject* object) override;
		virtual void Attack(TileObject* object, Vector2 target)override;
		virtual void OnAttacked() = 0;

	protected:
		int mMaxHealth;
		int mHealth;
		int mDigPower;
		int mGold;
	};
}

