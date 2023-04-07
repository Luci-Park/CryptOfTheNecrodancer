#pragma once
#include "LGameCharacter.h"
namespace cl
{
	class Item;
	class Tool;
	class SpriteRenderer;
	class AudioClip;
	class CadenceShovelEffect;
	class CadenceSound;
	class Cadence : public GameCharacter
	{
	public:
		Cadence(Scene* scene);
		~Cadence();

		virtual void Initialize()					override;
		virtual void Update()						override;
		virtual void Render(HDC hdc)				override;

		virtual void OnAttacked(float attackPower)	override;
		virtual void OnDestroy() override;

		virtual void OnBeat() override;
		virtual void OnBeatChanged() override;

		void SwitchItem(Item* item, eItemTypes type);
		Vector2 GetPos() { return mIndex; }
		Vector2 GetInput() { return mInput; }
	protected:
		virtual bool TryAttack(Vector2 direction)	override;
		//Returns true if InteractedWithDig;
		virtual bool TryDig(Vector2 direction)		override;
		virtual bool TryMove(Vector2 direction)		override;

	private:
		void OnMove(Vector2 direction);
		void SetInput();
		void SetSprite();
		virtual void PlayOnAttackSound()			override;
		virtual void PlayOnHitSound()				override;
		virtual void PlayOnDeathSound()				override;

	private:
		Item* mItems[(int)eItemTypes::Size];
		Tool* mShovel;
		SpriteRenderer* mSpriteRenderer;
		CadenceShovelEffect* mShovelEffect;
		CadenceSound* mSound;
		Vector2 mInput;
		int consecutiveHits;

	};

}

