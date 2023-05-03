#pragma once
#include "LMonster.h"
#include "LLightSource.h"
#include "LKing.h"
namespace cl
{
	class PiecesSprite;
	class Pieces : public Monster
	{
	public:
		Pieces(Scene* sc);
		virtual ~Pieces();
		virtual void Initialize() override = 0;
		void SetInitialBeat(int beat) { mBeatCount = beat; }
		void SetKing(King* king) { mKing = king; }

		virtual void OnDestroy() override;
	protected:
		virtual Vector2 GetNextDir() override = 0;
		virtual void SetStats() override;

		virtual void PlayOnAttackSound();
		virtual void PlayOnHitSound();
		virtual void PlayOnDeathSound();

		virtual void Recoil(Vector2 dir)	override {};
		virtual void OnBeat()				override;
	protected:
		PiecesSprite* mPieceSprite;
		int mBeatCount;
		int mMoveBeat;

		AudioClip* mAttackSound;
		AudioClip* mDeathSounds[3];
		LightSource* mLightSource;

		King* mKing;
	};
}

