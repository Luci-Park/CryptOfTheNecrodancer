#include "LSkeleton.h"
namespace cl
{
    Skeleton::Skeleton(Scene* sc)
        :SkeletonBase(sc)
    {
    }
    Skeleton::~Skeleton()
    {
    }
    int Skeleton::GetY()
    {
        return 0;
    }
    void Skeleton::SetStats()
    {
        mActivationRadius = 3;
        mMaxHealth = 1;
        mAttackPower = 0.5f;
        mDrop = 2;
    }
    GreenSkeleton::GreenSkeleton(Scene* sc)
        :SkeletonBase(sc)
    {
    }
    GreenSkeleton::~GreenSkeleton()
    {
    }
    int GreenSkeleton::GetY()
    {
        return 1;
    }
    void GreenSkeleton::SetStats()
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