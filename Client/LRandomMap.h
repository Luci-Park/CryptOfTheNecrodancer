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
		void CreateExitRoom();
		void CreateStartRoom();
		void SetRoom(int sectionY, int sectionX);
		void CopyRooms();
		void CopyRoom(Room* room);
		void DeleteRooms();
		bool DoesRoomOverlap(Vector2 l1, Vector2 r1, Vector2 l2, Vector2 r2);
		Room* mRooms[3][3];
		int section[3][2];
		int mZone; 
	};
}

