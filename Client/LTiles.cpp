//#include "LTiles.h"
//namespace cl
//{
//	const int TileInfo::tileUnit = 24;
//	const Vector2 TileInfo::wallSpriteSize = Vector2(24.0f, 48.0f);
//	const float TileInfo::tileScale = 2.0f;
//
//
//	Sprite TileInfo::GetWallTile(eWallSpriteTypes tileType)
//	{
//		Sprite sprite;
//		Vector2 index = wallIndex[(int)tileType];
//		sprite.leftTop.x = index.x * wallSpriteSize.x;
//		sprite.leftTop.y = index.y * wallSpriteSize.y;
//		sprite.size = Vector2(24.0f, 39.0f);
//		sprite.offset = Vector2(-12.0f, -15.0f);
//		return sprite;
//	}
//}