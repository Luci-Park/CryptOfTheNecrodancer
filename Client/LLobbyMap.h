#pragma once
#include "LMap.h"
namespace cl
{
	class LobbyMap : public Map
	{
	public:
		LobbyMap();
		~LobbyMap();
	private:
		virtual void CreateMapBluePrint() override;
		void SetFloor();
		void SetWall();
		void SetLights();
	};
}

