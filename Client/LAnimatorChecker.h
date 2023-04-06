#pragma once
#include "LGameObject.h"

namespace cl
{
	class AnimatorChecker : public GameObject
	{
	public:
		AnimatorChecker(Scene* scene);
		virtual ~AnimatorChecker();

		virtual void Initialize();
	};
}

