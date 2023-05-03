#include "LFloorTile.h"
#include "LSceneManager.h"
#include "LFloorStrategy.h"
namespace cl
{
	StairTile::StairTile(Scene* sc)
		:FloorTile(sc)
		, mbIsLocked(false)
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
		FloorTile::SetIndex(index);
		mCurrStrategy = new StairStrategy(this);
	}
	void StairTile::LoadScene()
	{
		SceneManager::LoadScene(mMoveScene);
	}
	void StairTile::SetLock(bool isLocked)
	{
		mbIsLocked = isLocked;
		if(mCurrStrategy != nullptr)
			mCurrStrategy->OnBeat();
	}
}