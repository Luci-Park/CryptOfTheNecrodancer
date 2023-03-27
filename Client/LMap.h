#pragma once
#include "LuciEngine.h"
#include "LFloorTile.h"
#include "LBeatObject.h"
namespace cl
{

	class Map : public BeatObject
	{
	public:
		Map();
		~Map();
		virtual void CreateMap(Scene* sc);
		virtual void OnBeat();
		virtual void OnBeatChanged() {}

		Vector2 GetStartPos();
	protected:
		Vector2 size;
		Vector2 startPos;
		std::vector<std::vector<FloorTile::eFloorTypes>> mFloorBluePrint;
		std::vector<std::vector<FloorTile*>> mFloor;
	};
	class LobbyMap : public Map
	{
	public:
		LobbyMap();
	private:

	};

	class TutorialMap : public Map
	{

	};

}