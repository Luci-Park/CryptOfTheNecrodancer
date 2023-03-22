#pragma once
#include "LScene.h"
namespace cl
{
	class Image;
	class TitleScene : public Scene
	{
	public:
		TitleScene();
		~TitleScene();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void Render(HDC hdc)override;
		virtual void Destroy()override;

		virtual void OnEnter()override;
		virtual void OnExit()override;

	private:
		Image* mBackground;
		Image* mButton;
		float timer;
	};
}
