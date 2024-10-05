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
		if (!mbIsInSightLine)
		{
			int x0 = playerPos.x, y0 = playerPos.y;
			int x1 = mIndex.x, y1 = mIndex.y;
			int dx = abs(x1 - x0), dy = abs(y1 - y0);
			int sx = x0 < x1 ? 1 : -1, sy = y0 < y1 ? 1 : -1;
			int err = dx - dy;
			while (true)
			{
				if (x0 == x1 && y0 == y1) {
					mbIsInSightLine = true;
					break;
				}
				//중복 방지
				MapManager::GetLight(Vector2(x0, y0))->InSight();

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
