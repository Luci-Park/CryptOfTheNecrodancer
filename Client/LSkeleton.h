#pragma once
#include "LSkeletonBase.h"
namespace cl
{
	class Skeleton :public SkeletonBase
	{
	public:
		Skeleton(Scene* sc);
		virtual ~Skeleton();
		
	private:
		virtual int GetY() override;
		virtual void SetStats() override;

	};

	class GreenSkeleton :public SkeletonBase
	{
	public:
		GreenSkeleton(Scene* sc);
		virtual ~GreenSkeleton();

	private:
		virtual int GetY() override;
		virtual void SetStats() override;
	};

	class BlackSkeleton :public SkeletonBase
	{
	public:
		BlackSkeleton(Scene* sc);
		virtual ~BlackSkeleton();

	private:
		virtual int GetY() override;
		virtual void SetStats() override;
	};
}
