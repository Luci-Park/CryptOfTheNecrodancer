#pragma once
#include "LGameCharacter.h"
namespace cl
{
	class Item;
	class Tool;
	class Weapon;
	class SpriteRenderer;
	class AudioClip;
	class CadenceAttackEffect;
	class CadenceShovelEffect;
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
	protected:
		virtual bool TryAttack(Vector2 direction)	override;
		//Returns true if InteractedWithDig;
		virtual bool TryDig(Vector2 direction)		override;
		virtual bool TryMove(Vector2 direction)		override;

	private:
		void OnMove(Vector2 direction);
		void GetInput();
		void SetSprite();
		void PlayOnDigSound();
		virtual void PlayOnAttackSound()			override;
		virtual void PlayOnHitSound()				override;
		virtual void PlayOnDeathSound()				override;
		void SetAudioClip();
		void SetDigSound();
		void SetAttackSound();
		void SetDeathSound();
		void SetOnHitSound();
	private:
		Item* mItems[(int)eItemTypes::Size];
		Tool* mShovel;
		Weapon* mWeapon;
		SpriteRenderer* mSpriteRenderer;
		CadenceShovelEffect* mShovelEffect;
		Vector2 mInput;
		int consecutiveHits;
#pragma region Sounds
		std::vector<AudioClip*> mDigVoice;
		std::vector<std::vector<AudioClip*>>mMeleeHitVoice;
		std::vector<AudioClip*>mRangedHitVoice;
		std::vector<AudioClip*>mDeathVoice;
		std::vector<AudioClip*>mOnAttackedVoice;
		AudioClip*mHitSFX;
		AudioClip*mDeathSFX;
#pragma endregion

	};

}

