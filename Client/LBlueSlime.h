#pragma once
#include "LSlime.h"
#include "LBehaviorTree.h"
namespace cl
{
	class BlueSlimeSprite;
	class BlueSlime : public Slime
	{
	public:
		BlueSlime(Scene* sc);
		~BlueSlime();

		virtual void Initialize()		override;
		virtual void Update()			override;
		virtual void Render(HDC hdc)	override;

		virtual void Sink()				override;

		virtual void OnBeat()			override;
		virtual void OnLateBeat()		override;
	private:
		virtual void SetStats() override;
		virtual Vector2 GetNextDir() override;
	private:
		BlueSlimeSprite* mSlimeSprite;
		int mMovementIndex;
		std::vector<Vector2> nextPos;
		bool mbMoveFailed;
	};
}

