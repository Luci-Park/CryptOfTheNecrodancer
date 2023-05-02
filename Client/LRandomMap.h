#pragma once
#include "LMap.h"
#define MAPSIZE 30
#define MARGIN 8
#define STARTIDX 3
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
		void CreateRooms(Room* parent);
		bool IsDirPossible(Vector2 dir, Room* parent, Room* child);
		bool SetRoomY(int x, Room* parent, Room* child);
		bool SetRoomX(int y, Room* parent, Room* child);
		void CopyRooms();
		void CopyRoom(Room* room);
		void CreateCorridor();
		void CreateCorridor(Room* parent, Room* child, Vector2 dir);
		void DeleteRooms();
		bool DoesRoomOverlap(Vector2 l1, Vector2 r1, Vector2 l2, Vector2 r2);
		std::vector<Room*>mRooms;

		int mZone; 
	};
}

