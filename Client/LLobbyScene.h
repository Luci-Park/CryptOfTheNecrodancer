#pragma once
#include "LScene.h"
namespace cl
{
	class AudioClip;
	class BeatManager;
	class LobbyScene : public Scene
	{
	public:
		LobbyScene();
		virtual ~LobbyScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnEnter() override;
		virtual void OnExit() override;
	private:
		AudioClip* mBGM;
	};
}

