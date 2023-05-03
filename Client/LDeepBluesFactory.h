#pragma once
#include "LuciEngine.h"
namespace cl
{
	class TileObject;
	class Scene;
	class DeepBluesFactory
	{
	public:
		static TileObject* CreateBoss(Vector2 index, Scene* scene);
	};
}

