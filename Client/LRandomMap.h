#pragma once
#include "LMap.h"
namespace cl
{
	class Room;
	class RandomMap : public Map
	{
	public:
		RandomMap();
		virtual ~RandomMap();
	private:
		virtual void CreateMapBluePrint() override;
		void InitializeWall();
		void CreateRoom();
		void SetRoom(int idx);
		void CopyRooms();
		void CopyRoom(Room* room);
		void DeleteRooms();
		std::vector<Room*> mRooms;
		int mZone; 
	};
}

