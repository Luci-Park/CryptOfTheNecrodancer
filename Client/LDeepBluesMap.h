#pragma once
#include "LMap.h"
namespace cl
{
	class DeepBluesMap : public Map
	{
	public:
		DeepBluesMap();
		~DeepBluesMap();
		virtual void Update() override;
	private:
		virtual void CreateMapBluePrint() override;
		void SetTop();
		void SetArena();
		void SetBottom();
		int topY, arenaY, bottomY;
		bool mbEntered;
		bool mbExited;
	};
}

