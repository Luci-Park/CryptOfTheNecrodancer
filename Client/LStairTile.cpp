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
		if (mCurrStrategy != nullptr)
		{
			delete mCurrStrategy;
			mCurrStrategy = nullptr;
		}
	}
	
	void StairTile::SetIndex(Vector2 index)
	{
		mCurrStrategy = new StairStrategy(this);
		mIndex = index;
	}
	
	void StairTile::OnInteract(TileObject* object)
	{
		if (!mIsLocked)
			SceneManager::LoadScene(mMoveScene);
	}
}