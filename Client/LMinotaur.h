#pragma once
#include "LMinotaurBase.h"
namespace cl
{
	class LightMinotaur : public MinotaurBase
	{
	public:
		LightMinotaur(Scene* sc);
		virtual ~LightMinotaur();
	private:
		virtual void SetStats() override;
		virtual int GetY() override;
	};
	class DarkMinotaur : public MinotaurBase
	{
	public:
		DarkMinotaur(Scene* sc);
		virtual ~DarkMinotaur();
	private:
		virtual void SetStats() override;
		virtual int GetY() override;
	};
}

