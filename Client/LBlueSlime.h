#pragma once
#include "LGameCharacter.h"
#include "LBehaviorTree.h"
namespace cl
{
	class BlueSlimeSprite;
	class BlueSlime : public GameCharacter
	{
	public:
		BlueSlime(Scene* sc);
		~BlueSlime();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void Sink() override;

		virtual void OnAttacked(float attackPower)override;
		virtual void OnDestroy() override;

		virtual void OnBeat();
	private:
		virtual bool TryAttack(Vector2 Direction) override;
		//Returns true if InteractedWithDig;
		virtual bool TryDig(Vector2 direction) override;
		virtual bool TryMove(Vector2 direction) override;
	private:
		BlueSlimeSprite* mSlimeSprite;
		Vector2 GetNextPos();
		int mMovementIndex;
		std::vector<Vector2> nextPos;
		bool mbMoveFailed;
	};
}

