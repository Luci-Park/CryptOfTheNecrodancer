#include "LMonsterHeart.h"
#include "LImage.h"
#include "LResources.h"
#include "LCamera.h"
namespace cl
{
	MonsterHeart::MonsterHeart(Scene* sc)
		:GameObject(sc, false)
		, mCurrHeart(0)
		, mMaxHeart(0)
	{
		mFullHeart = Vector2(226, 29);
		mEmptyHeart = Vector2(240, 29);
		mSpriteSize = Vector2(13, 11);
		mOffset = Vector2(mSpriteSize.x * 0.5, mSpriteSize.y);
	}
	MonsterHeart::~MonsterHeart()
	{
	}
	void MonsterHeart::Initialize()
	{
		GameObject::Initialize();
		mHeartImage = Resources::Load<Image>(L"HUD", L"..\\Assets\\Arts\\Effects\\HUD.bmp");
	}

	void MonsterHeart::Update()
	{
		GameObject::Update();
	}

	void MonsterHeart::Render(HDC hdc)
	{
		GameObject::Render(hdc);
		Vector2 startPos = mStartPos + mTransform->GetPos();
		startPos = Camera::CaluatePos(startPos);
		if (Camera::IsDrawable(Sprite(startPos, Vector2(mSpriteSize.x * UNITSCALE * mMaxHeart, mSpriteSize.y * UNITSCALE), Vector2::Zero)))
		{
			for (int i = mMaxHeart; i > 0; --i)
			{
				if (i <= mCurrHeart)
					DrawHeart(hdc, startPos, mFullHeart);
				else
					DrawHeart(hdc, startPos, mEmptyHeart);
				startPos.x += mSpriteSize.x * UNITSCALE;
			}
		}
	}

	void MonsterHeart::DrawHeart(HDC hdc, Vector2 imageLeftTop, Vector2 spriteLeftTop)
	{
		TransparentBlt(hdc, imageLeftTop.x, imageLeftTop.y
			, mSpriteSize.x * UNITSCALE, mSpriteSize.y * UNITSCALE
			, mHeartImage->GetHdc(), spriteLeftTop.x, spriteLeftTop.y
			, mSpriteSize.x, mSpriteSize.y, RGB(255, 0, 255));
	}

	void MonsterHeart::SetHearts(int maxHealth, int currHealth)
	{
		mMaxHeart = maxHealth;
		mCurrHeart = currHealth;
		mStartPos.x = mMaxHeart * mSpriteSize.x * UNITSCALE* 0.5 * -1;
		mStartPos.y = mSpriteSize.y * UNITSCALE * -1;
	}


}