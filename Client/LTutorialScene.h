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
		virtual void Update()override;

	private:
		GameManager* mGameManager;
	};
}

