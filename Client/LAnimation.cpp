#include "LAnimation.h"
#include "LTime.h"
#include "LImage.h"
#include "LAnimator.h"
#include "LTransform.h"
#include "LGameObject.h"
#include "LCamera.h"

namespace cl
{
    Animation::Animation()
        : mAnimator(nullptr)
        , mSheetImage(nullptr)
        , mTime(0.0f)
        , mbComplete(false)
        , mSpriteIndex(0)
    {
        
    }

    Animation::~Animation()
    {
    }

    void Animation::Initialize()
    {
    }

    void Animation::Update()
    {
        if (mbComplete == true)
            return;

        mTime += Time::DeltaTime();
        if (mDuration < mTime)
        {
            mTime = 0.0f;
            if (mbReverse)
            {
                if (0 == mSpriteIndex)
                {
                    mbComplete = true;
                }
                else
                {
                    mSpriteIndex--;
                }
            }
            else
            {
                if (mSpriteSheet.size() <= mSpriteIndex + 1)
                {
                    mbComplete = true;
                }
                else
                {
                    mSpriteIndex++;
                }
            }
        }
    }

    void Animation::Render(HDC hdc)
    {
        Transform* tr 
            = mAnimator->GetOwner()->GetComponent<Transform>();
        Vector2 scale = tr->GetScale();

        Vector2 pos = tr->GetPos();
        pos += Vector2(mSpriteSheet[mSpriteIndex].offset.x * scale.x, mSpriteSheet[mSpriteIndex].offset.y * scale.y);
        if (!mAnimator->GetOwner()->IsUI())
            pos = Camera::CaluatePos(pos);
        Vector2 Percent = mAnimator->GetPercent();
        Vector2 spriteRightBottom = Vector2(mSpriteSheet[mSpriteIndex].size.x * Percent.x, mSpriteSheet[mSpriteIndex].size.y * Percent.y);
        Vector2 resltRightBottom = Vector2(mSpriteSheet[mSpriteIndex].size.x * scale.x * Percent.x, mSpriteSheet[mSpriteIndex].size.y * scale.y * Percent.y);
        Sprite rect = { pos, resltRightBottom, Vector2::Zero };
        if (Camera::IsDrawable(rect))
        {
            TransparentBlt(hdc, pos.x, pos.y
                , resltRightBottom.x, resltRightBottom.y
                , mSheetImage->GetHdc()
                , mSpriteSheet[mSpriteIndex].leftTop.x, mSpriteSheet[mSpriteIndex].leftTop.y
                , spriteRightBottom.x, spriteRightBottom.y, RGB(255, 0, 255));
        }
    }

    void Animation::Create(Image* sheet, UINT coulmn, UINT row, 
        UINT sCol, UINT sRow, UINT spriteLength
        , Vector2 offset, float duration)
    {
        mSheetImage = sheet;
        if (sCol > coulmn || sRow > row) return;
        Vector2 size = Vector2::One;
        size.x = mSheetImage->GetWidth() / (float)coulmn;
        size.y = mSheetImage->GetHeight() / (float)row;
        Vector2 leftTop = Vector2(size.x * sCol, size.y * sRow);

        for (size_t i = 0; i < spriteLength; i++)
        {
            Sprite spriteInfo;

            spriteInfo.leftTop.x = leftTop.x + (size.x * i);
            spriteInfo.leftTop.y = leftTop.y;
            if (spriteInfo.leftTop.x >= sheet->GetWidth())
            {
                leftTop.y += size.y;
                spriteInfo.leftTop.x = leftTop.x;
                spriteInfo.leftTop.y = leftTop.y;
            }
            spriteInfo.size = size;
            if (offset == Vector2::Zero)
                spriteInfo.offset = offset - size / 2;
            else
                spriteInfo.offset = offset;
            mSpriteSheet.push_back(spriteInfo);
        }
        SetDuration(duration);
    }
    void Animation::Create(Image* sheet, Vector2 leftTop, Vector2 size, UINT spriteLength, Vector2 offset, float duration)
    {
        mSheetImage = sheet;
        for (int i = 0; i < spriteLength; i++)
        {
            Sprite spriteInfo;

            spriteInfo.leftTop = leftTop + size * i;
            spriteInfo.size = size;
            if (offset == Vector2::Zero)
                spriteInfo.offset = offset - size / 2;
            else
                spriteInfo.offset = offset;
            mSpriteSheet.push_back(spriteInfo);
        }
        SetDuration(duration);        
    }

    void Animation::Reset()
    {
        mSpriteIndex = mbReverse ? mSpriteSheet.size() - 1: 0;
        mTime = 0.0f;
        mbComplete = false;
    }
}
