#pragma once
#include "LSkeletonBase.h"
namespace cl
{
	class WhiteSkeleton :public SkeletonBase
	{
	public:
		WhiteSkeleton(Scene* sc);
		virtual ~WhiteSkeleton();
		
	private:
		virtual int GetY() override;
		virtual void SetStats() override;

	};

	class YellowSkeleton :public SkeletonBase
	{
	public:
		YellowSkeleton(Scene* sc);
		virtual ~YellowSkeleton();

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
