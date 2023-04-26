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
	class Cadence : public GameCharacter
	{
	public:
		Cadence(Scene* scene);
		~Cadence();

		virtual void Initialize()					override;
		virtual void Update()						override;
		virtual void Render(HDC hdc)				override;

		virtual void OnAttacked(float attackPower, Vector2 dir)	override;
		virtual bool TryMove()						override;
		virtual void OnDestroy()					override;

		virtual void OnBeat()						override;
		virtual void OnLateBeat()					override;
		virtual void OnBeatChanged()				override;

		void SwitchItem(Item* item, eItemTypes type);
		Vector2 GetPos() { return mIndex; }
		Vector2 GetInput() { return mInput; }

	protected:
		virtual bool TryAttack(Vector2 direction)	override;
		//Returns true if InteractedWithDig;
		virtual bool TryDig(Vector2 direction)		override;
	private:
		void OnMove(Vector2 direction);
		void SetInput();
		void SetSprite();

		Tool* mShovel() { return (Tool*)mItems[(int)eItemTypes::Tool]; }
		Weapon* mWeapon() { return (Weapon*)mItems[(int)eItemTypes::Weapon]; }

		virtual void PlayOnAttackSound()			override;
		virtual void PlayOnHitSound()				override;
		virtual void PlayOnDeathSound()				override;

	private:
		Health* mHealth;
		Item* mItems[(int)eItemTypes::Size];
		LightSource* mLightSource;
		CadenceShovelEffect* mShovelEffect;
		CadenceSound* mSound;
		Vector2 mInput;
		int consecutiveHits;
		bool mMoved;
	};

}

