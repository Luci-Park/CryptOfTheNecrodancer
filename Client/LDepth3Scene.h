#pragma once
#include "LScene.h"
namespace cl
{
	class AudioClip;
	class BeatManager;
	class Depth3Scene : public Scene
	{
	public:
		Depth3Scene();
		virtual ~Depth3Scene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnEnter() override;
		virtual void OnExit() override;
	private:
		AudioClip* mBGM;
	};
}

