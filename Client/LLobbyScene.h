#pragma once
#include "LScene.h"
namespace cl
{
	class BeatManager;
	class LobbyScene : public Scene
	{
	public:
		LobbyScene();
		virtual ~LobbyScene();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;
	};
}

