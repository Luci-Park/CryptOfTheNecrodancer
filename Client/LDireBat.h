#include "LDireBatBase.h"
#pragma once
namespace cl
{
	class YellowDireBat : public DireBatBase
	{
	public:
		YellowDireBat(Scene* sc);
		virtual ~YellowDireBat();

	private:
		virtual int GetY() override { return 0; }
		virtual void SetStats() override;
	};
	class BrownDireBat : public DireBatBase
	{
	public:
		BrownDireBat(Scene* sc);
		virtual ~BrownDireBat();

	private:
		virtual int GetY() override { return 1; }
		virtual void SetStats() override;
	};
}

