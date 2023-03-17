#pragma once
#include "LGameObject.h"
namespace cl
{
	class Image;
	class ArrowUI : public GameObject
	{
	public:
		ArrowUI();
		virtual ~ArrowUI();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Image* mImage;
	};
}

