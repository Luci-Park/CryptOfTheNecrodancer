#include "LSkeletonSprite.h"
#include "LAnimator.h"
#include "LResources.h"
namespace cl
{
    SkeletonSprite::SkeletonSprite(Scene* sc)
        : CharacterSprite(sc)
        , mbLostHead(false)
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
        idleAnimation[2] = L"UpIdle";
        raiseHandAnimation[0] = L"RightHand";
        raiseHandAnimation[1] = L"LeftHand";
        raiseHandAnimation[2] = L"UpHand";
        noHead = L"NoHead";
        std::wstring leftPath = L"..\\Assets\\Arts\\Monsters\\Skeleton\\skeletons_left.bmp";
        std::wstring rightPath = L"..\\Assets\\Arts\\Monsters\\Skeleton\\skeletons_right.bmp";
        mAnimator->CreateAnimation(idleAnimation[GetIndex(Vector2::Right)], L"skeletons_right", rightPath, 17, 6, 13, skeleY, 4, Vector2::Zero, 0.36f);
        mAnimator->CreateAnimation(raiseHandAnimation[GetIndex(Vector2::Right)], L"skeletons_right", rightPath, 17, 6, 9, skeleY, 4, Vector2::Zero, 0.36f);
        mAnimator->CreateAnimation(idleAnimation[GetIndex(Vector2::Left)], L"skeletons_left", leftPath, 17, 6, 0, skeleY, 4, Vector2::Zero, 0.36f);
        mAnimator->CreateAnimation(raiseHandAnimation[GetIndex(Vector2::Left)], L"skeletons_left", leftPath, 17, 6, 4, skeleY, 4, Vector2::Zero, 0.36f);
        mAnimator->CreateAnimation(idleAnimation[GetIndex(Vector2::Up)], L"skeletons_left", leftPath, 17, 6, 8, skeleY, 4, Vector2::Zero, 0.36f);
        mAnimator->CreateAnimation(raiseHandAnimation[GetIndex(Vector2::Up)], L"skeletons_left", leftPath, 17, 6, 12, skeleY, 4, Vector2::Zero, 0.36f);
        mAnimator->CreateAnimation(noHead, L"skeletons_left", leftPath, 17, 6, 16, skeleY, 1, Vector2::Zero, 0.36f);
        Idle();
    }
    void SkeletonSprite::Turn(Vector2 dir)
    {
        if (dir == Vector2::Down)
        {
            if (mLookDir == Vector2::Up)
                mLookDir = Vector2::Right;
        }
        else if(dir == Vector2::Left || dir == Vector2::Right || dir == Vector2::Up)
        {
            mLookDir = dir;
        }
    }
    void SkeletonSprite::Idle()
    {
        if (mbLostHead) return;
        int idx = GetIndex(mLookDir);
        bool rev = mLookDir == Vector2::Right;
        if (!mAnimator->IsAnimationPlaying(idleAnimation[idx]))
            mAnimator->Play(idleAnimation[idx], true, rev);
    }
    void SkeletonSprite::RaiseHand()
    {
        if (mbLostHead) return;
        int idx = GetIndex(mLookDir);
        bool rev = mLookDir == Vector2::Right;
        if (!mAnimator->IsAnimationPlaying(raiseHandAnimation[idx]))
            mAnimator->Play(raiseHandAnimation[idx], true, rev);
    }
    void SkeletonSprite::LostHead()
    {
        mbLostHead = true;
        mAnimator->Play(noHead, true, false);
    }
    int SkeletonSprite::GetIndex(Vector2 dir)
    {
        if (dir == Vector2::Right)
            return 0;
        if (dir == Vector2::Left)
            return 1;
        if (dir == Vector2::Up)
            return 2;
        return 0;
    }
}
