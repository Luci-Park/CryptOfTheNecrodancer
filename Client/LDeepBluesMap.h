#pragma once
#include "LMap.h"
namespace cl
{
	class DeepBluesMap : public Map
	{
	public:
		DeepBluesMap();
		~DeepBluesMap();
	private:
		virtual void CreateMapBluePrint() override;
		void SetFloor();
		void SetWall();
		void SetLights();

	};
}

