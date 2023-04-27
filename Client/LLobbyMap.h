#pragma once
#include "LMap.h"
namespace cl
{
	class LobbyMap : public Map
	{
	public:
		LobbyMap();
	private:
		virtual void SetFloor();
		virtual void SetWall();
	};
}

