#pragma once
#include "LGameObject.h"
namespace cl
{
	class Tile : public GameObject
	{
	public:
		Tile(Scene* sc);
		~Tile();
		void Reset();
	private:
		bool revealed;
		float brightness;
	};
}

