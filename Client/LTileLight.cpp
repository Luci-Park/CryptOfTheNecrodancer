#include "LTileLight.h"
#include "LMapManager.h"
namespace cl
{
	TileLight::TileLight(Vector2 index)
		: mIllumination(0.0)
		, mIsInSightLine(false)
		, mIsRevealed(false)
		, mIndex(index)
	{
	}
	TileLight::~TileLight()
	{
	}
	void TileLight::AddIllumination(float brightness)
	{
		mIllumination = std::clamp(mIllumination + brightness, 0.0f, 1.0f);
	}
	void TileLight::Reset()
	{
		mIllumination = 0.0f;
		mIsInSightLine = false;
	}
	void TileLight::CheckIfInSight(Vector2 playerPos)
	{
		if (!mIsInSightLine)
		{
			int x0 = playerPos.x;
			int y0 = playerPos.y;
			int x1 = mIndex.x;
			int y1 = mIndex.y;
			int dx = abs(x1 - x0);
			int dy = abs(y1 - y0);
			int sx = x0 < x1 ? 1 : -1;
			int sy = y0 < y1 ? 1 : -1;
			int err = dx - dy;
			while (true)
			{
				// Check if the end of the line has been reached
				if (x0 == x1 && y0 == y1) {
					mIsInSightLine = true;
					break;
				}
				// Check if the current tile is a wall
				if (MapManager::GetWall(Vector2(x0, y0)) != nullptr) {
					mIsInSightLine = false;
					break;
				}
				else
				{
					MapManager::GetLight(Vector2(x0, y0))->InSight();
				}
				int e2 = 2 * err;
				if (e2 > -dy)
				{
					err -= dy;
					x0 += sx;
				}
				if (e2 < dx)
				{
					err += dx;
					y0 += sy;
				}
			}
		}
		if (mIsInSightLine && mIllumination > 0.3f)
			mIsRevealed = true;
	}
}
