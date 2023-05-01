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
		void CreateRooms(int idx);
		bool IsDirPossible(Vector2 dir, int idx);
		void CopyRooms();
		void CopyRoom(Room* room);
		void DeleteRooms();
		bool DoesRoomOverlap(Vector2 l1, Vector2 r1, Vector2 l2, Vector2 r2);
		std::vector<Room*> mRooms;
		std::vector<Vector2> mDirections;
		int mZone; 
	};
}

