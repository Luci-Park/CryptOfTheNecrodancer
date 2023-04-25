#pragma once
#include "LBatBase.h"
namespace cl
{
	class BlueBat : public BatBase
	{
	public:
		BlueBat(Scene* sc);
		virtual ~BlueBat();

		virtual void Initialize() override;
		virtual void OnLateBeat() override;
	private:
		virtual void SetStats() override;
		virtual Vector2 GetNextDir() override;

	private:
		bool mbMove;
	};

	class RedBat : public BatBase
	{
	public:
		RedBat(Scene* sc);
		virtual ~RedBat();

		virtual void Initialize() override;
	protected:
		virtual void SetStats() override;

	};
}

