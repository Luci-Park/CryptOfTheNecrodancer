#pragma once
#include "LGameObject.h"
namespace cl
{
	class Image;
	class MonsterHeart : public GameObject
	{
	public:
		MonsterHeart(Scene* sc);
		~MonsterHeart();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC hdc)override;

		void SetHearts(int maxHealth, int currHealth);
	private:
		void DrawHeart(HDC hdc, Vector2 imageLeftTop, Vector2 spriteLeftTop);
	private:
		Image* mHeartImage;
		Vector2 mFullHeart;
		Vector2 mEmptyHeart;
		Vector2 mSpriteSize;
		Vector2 mOffset;

		int mMaxHeart;
		int mCurrHeart;
		Vector2 mStartPos;
	};
}

