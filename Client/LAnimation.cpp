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

    void Animation::Render(HDC hdc)
    {
        Transform* tr 
            = mAnimator->GetOwner()->GetComponent<Transform>();
        Vector2 scale = tr->GetScale();

        Vector2 pos = tr->GetPos();
        if (!mAnimator->GetOwner()->IsUI())
        pos = Camera::CaluatePos(pos);
        pos += mSpriteSheet[mSpriteIndex].offset;

        TransparentBlt(hdc, pos.x, pos.y
            , mSpriteSheet[mSpriteIndex].size.x * scale.x
            , mSpriteSheet[mSpriteIndex].size.y * scale.y
            , mSheetImage->GetHdc()
            , mSpriteSheet[mSpriteIndex].leftTop.x, mSpriteSheet[mSpriteIndex].leftTop.y
            , mSpriteSheet[mSpriteIndex].size.x, mSpriteSheet[mSpriteIndex].size.y,
            RGB(255, 0, 255));
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
            spriteInfo.size = size;
            spriteInfo.offset = offset - size / 2;
            mSpriteSheet.push_back(spriteInfo);
        }
        SetDuration(duration);
    }

    void Animation::Reset()
    {
        mSpriteIndex = 0;
        mTime = 0.0f;
        mbComplete = false;
    }

}
