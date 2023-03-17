#pragma once
#include "LGameObject.h"
namespace cl
{
	class SpriteRenderer;
	class StageBG : public GameObject
	{
	public:
		StageBG();
		~StageBG();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();
	private:
		void GetSprite();
	private:
		SpriteRenderer* mRenderer;
		
	};
}