#pragma once
#include "LMonster.h"
#include "LBehaviorTree.h"
namespace cl
{
	class BlueSlimeSprite;
	class BlueSlime : public Monster
	{
	public:
		BlueSlime(Scene* sc);
		~BlueSlime();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void Sink() override;

		virtual void OnAttacked(float attackPower)override;

		virtual void OnBeat();
	private:
		virtual void SetStats() override;
		virtual Vector2 GetNextDir() override;
		virtual bool TryMove(Vector2 direction) override;
	private:
		BlueSlimeSprite* mSlimeSprite;
		int mMovementIndex;
		std::vector<Vector2> nextPos;
		bool mbMoveFailed;
	};
}

