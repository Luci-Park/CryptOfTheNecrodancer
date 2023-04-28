#pragma once
#include "LMap.h"
namespace cl
{
	class RandomMap : public Map
	{
	public:
		RandomMap();
		~RandomMap();
	private:
		virtual void CreateMapBluePrint() override;
	};
}

