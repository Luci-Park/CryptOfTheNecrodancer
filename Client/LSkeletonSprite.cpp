#include "LSkeletonSprite.h"
#include "LAnimator.h"
#include "LResources.h"
namespace cl
{
    SkeletonSprite::SkeletonSprite(Scene* sc)
        : CharacterSprite(sc)
    {
        mLookDir = GetRandomInt(0, 1) ? Vector2::Right : Vector2::Left;
    }
    void SkeletonSprite::Initialize()
    {
        mAnimator = AddComponent<Animator>();
        CharacterSprite::Initialize();
    }
    void SkeletonSprite::SetSkeleY(int y)
    {
        skeleY = y * 2;
        mIdleAnimation[0] = L"RightIdle";
        mIdleAnimation[1] = L"LeftIdle";
        mIdleShadowAnimation[0] = L"ShadowRightIdle";
        mIdleShadowAnimation[1] = L"ShadowLeftIdle";
        mRaiseHandAnimation[0] = L"RightHand";
        mRaiseHandAnimation[1] = L"LeftHand";
        mHandShadowAnimation[0] = L"ShadowRight";
        mHandShadowAnimation[1] = L"ShadowLeft";
        mNoHead = L"NoHead";
        mNoHeadShadow = L"ShadowNoHead";
        std::wstring path = L"..\\Assets\\Arts\\Monsters\\Skeleton\\skeletons.bmp";
        mAnimator->CreateAnimation(mIdleAnimation[GetIndex(Vector2::Right)], L"skeletons", path, 17, 6, 12, skeleY, 4, -Vector2(12, 24), 0.36f);
        mAnimator->CreateAnimation(mIdleShadowAnimation[GetIndex(Vector2::Right)], L"skeletons", path, 17, 6, 12, skeleY + 1, 4, -Vector2(12, 24), 0.36f);
        mAnimator->CreateAnimation(mRaiseHandAnimation[GetIndex(Vector2::Right)], L"skeletons", path, 17, 6, 8, skeleY, 4, -Vector2(12, 24), 0.36f);
        mAnimator->CreateAnimation(mHandShadowAnimation[GetIndex(Vector2::Right)], L"skeletons", path, 17, 6, 8, skeleY + 1, 4, -Vector2(12, 24), 0.36f);

        mAnimator->CreateAnimation(mIdleAnimation[GetIndex(Vector2::Left)], L"skeletons", path, 17, 6, 0, skeleY, 4, -Vector2(12, 24), 0.36f);
        mAnimator->CreateAnimation(mIdleShadowAnimation[GetIndex(Vector2::Left)], L"skeletons", path, 17, 6, 0, skeleY + 1, 4, -Vector2(12, 24), 0.36f);
        mAnimator->CreateAnimation(mRaiseHandAnimation[GetIndex(Vector2::Left)], L"skeletons", path, 17, 6, 4, skeleY, 4, -Vector2(12, 24), 0.36f);
        mAnimator->CreateAnimation(mHandShadowAnimation[GetIndex(Vector2::Left)], L"skeletons", path, 17, 6, 4, skeleY + 1, 4, -Vector2(12, 24), 0.36f);

        mAnimator->CreateAnimation(mNoHead, L"skeletons", path, 17, 6, 16, skeleY, 1, -Vector2(12, 24), 0.36f);
        mAnimator->CreateAnimation(mNoHeadShadow, L"skeletons", path, 17, 6, 16, skeleY + 1, 1, -Vector2(12, 24), 0.36f);
    }
    void SkeletonSprite::Turn(Vector2 dir)
    {
        if(dir == Vector2::Left || dir == Vector2::Right)
        {
            mLookDir = dir;
        }
        if (mStatus == Status::RaiseHand)
            RaiseHand();
        else if (mStatus == Status::Idle)
            Idle();
        else if (mStatus == Status::NoHead)
            LostHead();
    }
    void SkeletonSprite::Idle()
    {
        if (mStatus == Status::NoHead) return;
        int idx = GetIndex(mLookDir);
        bool rev = mLookDir == Vector2::Right;
        if (!mbInShadows)
            mAnimator->Play(mIdleAnimation[idx], true, rev);
        else
            mAnimator->Play(mIdleShadowAnimation[idx], true, rev);
        mStatus = Status::Idle;
    }
    void SkeletonSprite::RaiseHand()
    {
        if (mStatus == Status::NoHead) return;
        int idx = GetIndex(mLookDir);
        bool rev = mLookDir == Vector2::Right;
        if (!mbInShadows)
            mAnimator->Play(mRaiseHandAnimation[idx], true, rev);
        else
            mAnimator->Play(mHandShadowAnimation[idx], true, rev);
        mStatus = Status::RaiseHand;
    }
    void SkeletonSprite::LostHead()
    {
        mStatus = Status::NoHead;
        if (!mbInShadows)
            mAnimator->Play(mNoHead, true, false);
        else
            mAnimator->Play(mNoHeadShadow, true, false);
    }
    int SkeletonSprite::GetIndex(Vector2 dir)
    {
        if (dir == Vector2::Right)
            return 0;
        if (dir == Vector2::Left)
            return 1;
        return 0;
    }
}
