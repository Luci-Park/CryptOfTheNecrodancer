#pragma once
#include "LGameCharacter.h"
namespace cl
{
	class Shovels;
	class SpriteRenderer;
	class AudioClip;
	class CadenceAttackEffect;
	class CadenceShovelEffect;
	class Cadence : public GameCharacter
	{
#pragma region Static Functions
	public:
		static void Reset();
		static Vector2 GetIndex() { return _mIndex; }
	private:
		static int _attackPower;
		static int _digPower;
		static int _health;
		static int _heartCount;
		static Vector2 _mIndex;
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

	private:
		void Move();
		void SetDigClip();
		void PlayDigClip();
	private:
		Shovels* shovel;
		SpriteRenderer* mSpriteRenderer;
		CadenceAttackEffect* mAttackEffect;
		CadenceShovelEffect* mShovelEffect;
		Vector2 pressedPos;
		
		AudioClip* mDigClip[6];
	};

}

