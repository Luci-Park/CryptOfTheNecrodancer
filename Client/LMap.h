#pragma once
#include "LuciEngine.h"
#include "LFloorTile.h"
#include "LWallTile.h"
#include "LItem.h"
#include "LTileLight.h"
#include "LMonsterFactory.h"
namespace cl
{
	class TileObject;
	class Cadence;
	class LightSource;
	class Map
	{
	public:
		Map();
		virtual ~Map();

		virtual void Update();
		void Render(HDC hdc);

		
		void AddLightSource(LightSource* light);
		void RemoveLightSource(LightSource* light);

		void SetLight(Vector2 pos, float brightness);
		TileLight* GetLight(Vector2 pos);
		void OnTileStep(TileObject* object, Vector2 pos);

		WallTile* GetWall(Vector2 index);
		TileObject* GetEnemy(Vector2 index);
		TileObject* GetTileObject(Vector2 index);
		Cadence* GetPlayerOnIndex(Vector2 index);
		Cadence* GetPlayer();
		Vector2 GetPlayerPos() { return mPlayerIndex; }
		Item* GetItem(Vector2 index);
		Vector2 SetItem(Item* item, Vector2 pos);

		void PlayerMove(TileObject* object, Vector2 src, Vector2 dest);
		void Move(TileObject* object, Vector2 src, Vector2 dest);
		
		bool IndexIsValid(Vector2 index);
		
		void CreateMap(Scene* sc);
		void SetKey(TileObject* key);

		static Vector2 GetTilePosOfIndex(Vector2 pos) { return pos * UNITLENGTH; }
		
		void DestroyTileObject(Vector2 index, TileObject* object);
		void DestroyWallObject(Vector2 index);
	protected:
		virtual void CreateMapBluePrint() = 0;
		virtual void OnKeyOpen();
		void CalculateLight();

		void Initialize(Vector2 size);
		void RenderMinimap(HDC hdc);

		Vector2 mMapSize;
		Vector2 mPlayerIndex;

		std::vector<std::vector<eFloorTypes>> mFloorBluePrint;
		std::vector<std::vector<eWallTypes>> mWallBluePrint;
		std::vector<std::vector<eMonsterTypes>> mMonsterBluePrint;
		std::vector<std::pair<Vector2, eSceneType>> mStairPos;
		std::vector<Vector2> mLightPos;
		std::vector<TileObject*>mKeyMonsters;

		void CreateFloor(Scene* sc);
		void CreateWall(Scene* sc);
		void CreateForeGround(Scene* sc);
		void CreateItems(Scene* sc);
		void CreatePlayer(Scene* sc);
		void CreateMonsters(Scene* sc);
		void CreateLight(Scene* sc);
		void CreateLightInfo();

		std::vector<std::vector<FloorTile*>> mFloor;
		std::vector<std::vector<WallTile*>> mWall;
		std::vector<std::vector<Item*>> mItems;
		std::vector<std::vector<TileObject*>> mTileObjects;
		std::vector<std::vector<TileLight*>> mLightStatus;
		std::vector<LightSource*>mLightSources;

	private:
		Color GetColor(int y, int x);
	};
}