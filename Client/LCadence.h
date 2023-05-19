#pragma once
#include "LGameCharacter.h"
#include "LItemIncludes.h"
namespace cl
{
	class AudioClip;
	class CadenceShovelEffect;
	class CadenceSound;
	class LightSource;
	class Health;
	class BeatJudge;
	class Cadence : public GameCharacter
	{
	public:
		static void Reset();
		Cadence(Scene* scene);
		~Cadence();

		virtual void Initialize()					override;
		virtual void Update()						override;
		virtual void Render(HDC hdc)				override;

		virtual bool OnAttacked(float attackPower, Vector2 dir)	override;
		virtual bool TryMove()						override;
		virtual void OnDestroy()					override;

		virtual void OnBeat()						override;
		virtual void OnLateBeat()					override;
		virtual void OnBeatChanged()				override;

		void SwitchItem(Item* item, eItemTypes type);
		void Heal(int amount);
		Vector2 GetPos() { return mIndex; }
		Vector2 GetPrevPos() { return mPrevPos; }
		bool HasMoved() { return mInput != Vector2::Zero; }
		void PlayVictory();

	protected:
		virtual bool TryAttack(Vector2 direction)	override;
		//Returns true if InteractedWithDig;
		virtual bool TryDig(Vector2 direction)		override;
	private:
		void OnMove(Vector2 direction);
		Vector2 CheckInput();
		void SetSprite();

		Tool* mShovel() { return (Tool*)mItems[(int)eItemTypes::Tool]; }
		Weapon* mWeapon() { return (Weapon*)mItems[(int)eItemTypes::Weapon]; }

		virtual void PlayOnAttackSound()			override;
		virtual void PlayOnHitSound()				override;
		virtual void PlayOnDeathSound()				override;

	private:
		Health* mHealth;
		Item* mItems[(int)eItemTypes::Size];
		BeatJudge* mJudge;
		LightSource* mLightSource;
		CadenceShovelEffect* mShovelEffect;
		CadenceSound* mSound;
		Vector2 mInput;
		Vector2 mPrevPos;
		int consecutiveHits;
		bool mMoved;
	};

}

