#pragma once
#include "LScene.h"
namespace cl
{
	class TempScene : public Scene
	{
	public:
		TempScene();
		virtual ~TempScene();

		virtual void Initialize() override;
	};
}

