#pragma once
#include "LSlime.h"
namespace cl
{
	class GreenSlimeSprite;
	class GreenSlime : public Slime
	{
	public:
		GreenSlime(Scene* sc);
		~GreenSlime();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void Sink() override;

		virtual void OnBeat();
	private:
		virtual void SetStats() override;
		virtual Vector2 GetNextDir() override;
		virtual bool TryMove(Vector2 direction) override;
	private:
		GreenSlimeSprite* mSlimeSprite;
		bool mbMoveFailed;
		AudioClip* mSlimeAttackSound;
		AudioClip* mSlimeDeathSound[3];
		AudioClip* mSlimeHitSound[3];

	};
}

