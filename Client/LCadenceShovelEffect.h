#pragma once
#include "LGameObject.h"
#include "LWallTile.h"
#include "LShovel.h"
namespace cl
{
	class SpriteRenderer;
	class CadenceShovelEffect : public GameObject
	{
	public:
		CadenceShovelEffect(Scene* sc);
		~CadenceShovelEffect();
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void OnDig(WallTile* wallTile, Shovels* shovel);
		void Show();
		void Reset();
	private:
		bool mbIsShowing;
		SpriteRenderer* mSpriteRenderer;
		float timer;
		float showTime;
	};
}

