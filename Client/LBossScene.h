#pragma once
#include "LScene.h"
namespace cl
{
	class AudioClip;
	class BossScene: public Scene
	{
	public:
		BossScene();
		virtual ~BossScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnEnter() override;
		virtual void OnExit() override;
	private:
		AudioClip* mBGM;
	};
}

