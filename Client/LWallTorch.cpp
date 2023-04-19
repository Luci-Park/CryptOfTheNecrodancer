#include "LWallTorch.h"
#include "LMapManager.h"
namespace cl
{
	WallTorch::WallTorch(Scene* sc)
		:TileObject(sc)
	{
	}
	void WallTorch::OnAttacked(float attackPower, Vector2 dir)
	{
	}
	void WallTorch::OnDestroy()
	{
		MapManager::DestroyTileObject(mIndex);
	}
	void WallTorch::SetBrightness()
	{
		mInnerRadius = 0.0;
		mOuterRadius = 4.25;
	}
}
