#include "LFloorTile.h"
#include "LSceneManager.h"
#include "LFloorStrategy.h"
#include "LCadence.h"
#include "LResources.h"
namespace cl
{
	StairTile::StairTile(Scene* sc)
		:FloorTile(sc)
		, mIsLocked(false)
	{
		mErrorSound = Resources::Load<AudioClip>(L"sfx_error_ST", L"..\\Assets\\Audio\\SoundEffects\\Floor\\sfx_error_ST.wav");
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
	
	void StairTile::OnInteract(TileObject* object)
	{
		Cadence* c = dynamic_cast<Cadence*>(object);
		if (c && !mIsLocked)
			SceneManager::LoadScene(mMoveScene);
		else if(c && mIsLocked)
		{
			mErrorSound->Play(false);
		}
	}
}