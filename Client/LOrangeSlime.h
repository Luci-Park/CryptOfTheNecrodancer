#pragma once
#include "LSlime.h"
namespace cl
{
	class OrangeSlimeSprite;
	class OrangeSlime : public Slime
	{
	public:
		OrangeSlime(Scene* sc);
		~OrangeSlime();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void Sink() override;

		virtual void OnBeat();
		virtual void OnLateBeat();
	private:
		virtual void SetStats() override;
		virtual Vector2 GetNextDir() override;
	private:
		OrangeSlimeSprite* mSlimeSprite;
		int mMovementIndex;
		std::vector<Vector2> nextPos;
		bool mbMoveFailed;
	};
}

