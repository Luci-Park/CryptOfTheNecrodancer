#pragma once
#include "LGameCharacter.h"
namespace cl
{
	class SpriteRenderer;
	class CadenceAttackEffect;
	class Cadence : public GameCharacter
	{
#pragma region Static Functions
	public:
		static void Reset();
	private:
		static int _attackPower;
		static int _digPower;
		static int _health;
		static int _heartCount;
#pragma endregion
	public:
		Cadence(Scene* scene);
		~Cadence();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnBeat() override;
		virtual void OnBeatChanged() override;
		
		virtual void Dig(TileObject* object) override;
		virtual void Attack(TileObject* object, Vector2 target) override;
		virtual void OnAttacked();

		void Move();
	private:
		SpriteRenderer* mSpriteRenderer;
		CadenceAttackEffect* mAttackEffect;
		Vector2 pressedPos;
	};

}

