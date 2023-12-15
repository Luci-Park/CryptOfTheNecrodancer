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

		virtual void Initialize()					override;
		virtual void Update()						override;
		virtual void Render(HDC hdc)				override;

		virtual void Sink()							override;
		virtual bool UnSink();

		virtual bool OnAttacked(float attackPower, Vector2 dir) override;
		virtual bool TryMove() override = 0;
		virtual void OnDestroy() = 0;

		virtual void OnBeat() = 0;
		virtual void OnBeatChanged();
		void SetSpeed(float speed) { mMoveSpeed = speed; }
	protected:
		virtual bool TryAttack(Vector2 Direction) = 0;
		virtual void Recoil(Vector2 dir);

		//Returns true if InteractedWithDig;
		virtual bool TryDig(Vector2 direction) = 0;

		virtual void PlayOnAttackSound() = 0;
		virtual void PlayOnHitSound() = 0;
		virtual void PlayOnDeathSound() = 0;
	protected:
		CharacterSprite* mSprite;
		Vector2 mMoveTarget;
		Vector2 prevDir;
		bool mbIsMoving;
		bool mbIsTouchingGround;
		bool mbIsSinked;
		bool mbMoveFailed;

		int mSize;

		float mMaxHealth;
		float mHealth;
		float mMoveSpeed;
	};
}

