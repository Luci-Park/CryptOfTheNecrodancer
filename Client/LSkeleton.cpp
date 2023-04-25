#include "LSkeleton.h"
namespace cl
{
    WhiteSkeleton::WhiteSkeleton(Scene* sc)
        :SkeletonBase(sc)
    {
    }
    WhiteSkeleton::~WhiteSkeleton()
    {
    }
    int WhiteSkeleton::GetY()
    {
        return 0;
    }
    void WhiteSkeleton::SetStats()
    {
        mActivationRadius = 3;
        mMaxHealth = 1;
        mAttackPower = 0.5f;
        mDrop = 2;
    }
    YellowSkeleton::YellowSkeleton(Scene* sc)
        :SkeletonBase(sc)
    {
    }
    YellowSkeleton::~YellowSkeleton()
    {
    }
    int YellowSkeleton::GetY()
    {
        return 1;
    }
    void YellowSkeleton::SetStats()
    {
        mActivationRadius = 3;
        mMaxHealth = 2;
        mAttackPower = 1.5f;
        mDrop = 3;
    }
    BlackSkeleton::BlackSkeleton(Scene* sc)
        :SkeletonBase(sc)
    {
    }
    BlackSkeleton::~BlackSkeleton()
    {
    }
    int BlackSkeleton::GetY()
    {
        return 2;
    }
    void BlackSkeleton::SetStats()
    {
        mActivationRadius = 3;
        mMaxHealth = 3;
        mAttackPower = 2.0f;
        mDrop = 4;
    }
}