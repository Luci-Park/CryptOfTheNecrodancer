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

	private:
		virtual void SetStats() override;
		virtual Vector2 GetNextDir() override;
	private:
		GreenSlimeSprite* mSlimeSprite;
		bool mbMoveFailed;
		AudioClip* mSlimeAttackSound;
		AudioClip* mSlimeDeathSound[3];
		AudioClip* mSlimeHitSound[3];

	};
}

