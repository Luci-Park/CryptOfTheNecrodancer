#pragma once
#include "LScene.h"
namespace cl
{
	class Image;
	class AudioClip;
	class TitleScene : public Scene
	{
	public:
		TitleScene();
		~TitleScene();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void Render(HDC hdc)override;

		virtual void OnEnter()override;
		virtual void OnExit()override;

	private:
		Image* mBackground;
		Image* mButton;
		AudioClip* mBGM;
	};
}

