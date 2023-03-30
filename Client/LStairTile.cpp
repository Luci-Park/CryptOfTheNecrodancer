#include "LFloorTile.h"
#include "LSceneManager.h"
#include "LFloorStrategy.h"
namespace cl
{
	StairTile::StairTile(Scene* sc)
		:FloorTile(sc)
		, mIsLocked(false)
	{
	}

	StairTile::~StairTile()
	{
	}
	
	void StairTile::SetIndex(Vector2 index)
	{
		mCurrStrategy = new StairStrategy(this);
		mIndex = index;
	}
	
	void StairTile::OnInteract()
	{
		if (!mIsLocked)
			SceneManager::LoadScene(mMoveScene);
	}
}