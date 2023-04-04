#pragma once
#include "LGameCharacter.h"
namespace cl
{
	class Shovels;
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

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnAttacked(float attackPower) override;
		virtual void OnDestroy() override;

		virtual void OnBeat() override;
		virtual void OnBeatChanged() override;
		
	protected:
		virtual bool TryAttack(Vector2 direction)override;
		//Returns true if InteractedWithDig;
		virtual bool TryDig(Vector2 direction) override;
		virtual bool TryMove(Vector2 direction) override;

	private:
		void GetInput();
		void SetSprite();
		bool UnSink();
		void SetDigClip();
		void PlayDigClip();
	private:
		Shovels* mShovel;
		Weapon* mWeapon;
		SpriteRenderer* mSpriteRenderer;
		CadenceShovelEffect* mShovelEffect;
		Vector2 mInput;
		AudioClip* mDigClip[6];
	};

}

