#include "LTileLight.h"
#include "LMapManager.h"
namespace cl
{
	bool TileLight::_VisionThroughWalls = false;

	TileLight::TileLight(Vector2 index)
		: mbIllumination(0.0)
		, mbIsInSightLine(false)
		, mbIsRevealed(false)
		, mIndex(index)
		, mbIsCompleteDark(false)
	{
	}
	TileLight::~TileLight()
	{
	}
	void TileLight::AddIllumination(float brightness)
	{
		mbIllumination = std::clamp(mbIllumination + brightness, 0.0f, 1.0f);
	}
	void TileLight::Reset()
	{
		mbIllumination = 0.0f;
		mbIsInSightLine = false;
		mbIsCompleteDark = false;
	}
	void TileLight::CheckIfInSight(Vector2 playerPos)
	{		
		//
		//mbIsInSightLine = true;
		//mbIllumination = 1.0f;
		//mbIsRevealed = true;
		//return;
		if (!mbIsInSightLine)
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
					mbIsInSightLine = true;
					break;
				}
				MapManager::GetLight(Vector2(x0, y0))->InSight();
				// Check if the current tile is a wall
				if (MapManager::GetWall(Vector2(x0, y0)) != nullptr) {
					mbIsInSightLine = false;
					break;
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
		if (mbIsInSightLine && mbIllumination > 0.3f)
			mbIsRevealed = true;
	}
}
