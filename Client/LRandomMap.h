#pragma once
#include "LMap.h"
namespace cl
{
	class Room;
	class RandomMap : public Map
	{
	public:
		RandomMap();
		~RandomMap();
	private:
		virtual void CreateMapBluePrint() override;
		void CopyRoom(Vector2 startPos, Room* room);
	};
}

