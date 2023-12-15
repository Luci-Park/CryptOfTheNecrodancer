#pragma once
#include "LMap.h"
#define MAPSIZE 30
#define MARGIN 8
#define STARTIDX 4
namespace cl
{
	class RoomBluePrint;
	class RandomMap : public Map
	{
	public:
		RandomMap(int zone);
		virtual ~RandomMap();
	private:
		virtual void OnKeyOpen() override;
		virtual void CreateMapBluePrint() override;

		void InitializeWall();
		void CreateRoomBluePrint();
		void CreateRoomBluePrint(RoomBluePrint* parent);
		bool IsDirPossible(Vector2 dir, RoomBluePrint* parent, RoomBluePrint* child);
		bool SetRoomY(int x, RoomBluePrint* parent, RoomBluePrint* child);
		bool SetRoomX(int y, RoomBluePrint* parent, RoomBluePrint* child);
		void CopyRoomsToFullBluePrint();
		void CopyRoom(RoomBluePrint* room);
		void CreateCorridor();
		void CreateCorridor(RoomBluePrint* parent, RoomBluePrint* child, Vector2 dir);
		void DeleteRooms();
		bool DoesRoomOverlap(Vector2 l1, Vector2 r1, Vector2 l2, Vector2 r2);
		bool IsIndexInRoom(Vector2 pos, RoomBluePrint* room);
		bool IsOnBoundary(Vector2 pos, RoomBluePrint* room);
		bool IsDigIndexValid(Vector2 index);
		std::vector<RoomBluePrint*>mRooms;

		int mZone; 
	};
}

