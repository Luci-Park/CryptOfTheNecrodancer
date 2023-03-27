#pragma once
#include "LScene.h"
namespace cl
{
	class GameManager;
	class TutorialScene : public Scene
	{
	public:
		TutorialScene();
		~TutorialScene();

		virtual void Initialize()override;
		virtual void Update()override;/*
		virtual void Render(HDC hdc)override;
		virtual void Destroy()override;

		virtual void OnEnter()override;
		virtual void OnExit()override;*/

	private:
		GameManager* mGameManager;
	};
}

