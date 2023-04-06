#pragma once
#include "LTileObject.h"
#include "LBeatObject.h"
namespace cl
{
	class BeatManager;
	class CharacterSprite;
	class GameCharacter : public TileObject, public BeatObject
	{
	public:
		GameCharacter(Scene* sc, bool isTouchingGround);
		virtual ~GameCharacter();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void Sink() override;
		virtual bool UnSink();

		virtual void OnAttacked(float attackPower);
		virtual void OnDestroy() = 0;

		virtual void OnBeat() = 0;
		virtual void OnBeatChanged();

	protected:
		virtual bool TryAttack(Vector2 Direction) = 0;
		void MoveFailed();

		//Returns true if InteractedWithDig;
		virtual bool TryDig(Vector2 direction) = 0;
		virtual bool TryMove(Vector2 direction) = 0;

		virtual void PlayOnAttackSound() = 0;
		virtual void PlayOnHitSound() = 0;
		virtual void PlayOnDeathSound() = 0;
	protected:
		CharacterSprite* mSprite;
		Vector2 mMoveTarget;
		bool mbIsMoving;
		bool mbIsTouchingGround;
		bool mbIsSinked;
		float mMaxHealth;
		float mHealth;
	};
}

