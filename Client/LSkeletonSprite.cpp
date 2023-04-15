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
        idleAnimation[0] = L"RightIdle";
        idleAnimation[1] = L"LeftIdle";
        raiseHandAnimation[0] = L"RightHand";
        raiseHandAnimation[1] = L"LeftHand";
        noHead = L"NoHead";
        std::wstring path = L"..\\Assets\\Arts\\Monsters\\Skeleton\\skeletons.bmp";
        mAnimator->CreateAnimation(idleAnimation[GetIndex(Vector2::Right)], L"skeletons", path, 17, 6, 12, skeleY, 4, -Vector2(12, 24), 0.36f);
        mAnimator->CreateAnimation(raiseHandAnimation[GetIndex(Vector2::Right)], L"skeletons", path, 17, 6, 8, skeleY, 4, -Vector2(12, 24), 0.36f);
        mAnimator->CreateAnimation(idleAnimation[GetIndex(Vector2::Left)], L"skeletons", path, 17, 6, 0, skeleY, 4, -Vector2(12, 24), 0.36f);
        mAnimator->CreateAnimation(raiseHandAnimation[GetIndex(Vector2::Left)], L"skeletons", path, 17, 6, 4, skeleY, 4, -Vector2(12, 24), 0.36f);
        mAnimator->CreateAnimation(noHead, L"skeletons", path, 17, 6, 16, skeleY, 1, -Vector2(12, 26), 0.36f);
    }
    void SkeletonSprite::Turn(Vector2 dir)
    {
        if(dir == Vector2::Left || dir == Vector2::Right)
        {
            mLookDir = dir;
            if (mStatus == Status::RaiseHand)
                RaiseHand();
            else if(mStatus == Status::Idle)
                Idle();
        }
    }
    void SkeletonSprite::Idle()
    {
        if (mStatus == Status::NoHead) return;
        int idx = GetIndex(mLookDir);
        bool rev = mLookDir == Vector2::Right;
        if (!mAnimator->IsAnimationPlaying(idleAnimation[idx]))
            mAnimator->Play(idleAnimation[idx], true, rev);
        mStatus = Status::Idle;
    }
    void SkeletonSprite::RaiseHand()
    {
        if (mStatus == Status::NoHead) return;
        int idx = GetIndex(mLookDir);
        bool rev = mLookDir == Vector2::Right;
        if (!mAnimator->IsAnimationPlaying(raiseHandAnimation[idx]))
            mAnimator->Play(raiseHandAnimation[idx], true, rev);
        mStatus = Status::RaiseHand;
    }
    void SkeletonSprite::LostHead()
    {
        mStatus = Status::NoHead;
        mAnimator->Play(noHead, true, false);
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
