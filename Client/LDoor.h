#pragma once
#include "LWallTile.h"
namespace cl
{
	class Door : public WallTile
	{
	public:
		Door(Scene* sc);
		~Door() {}
		
		virtual void Update() override;

		virtual bool OnCrumble() override;
		
		void SetHorizontal(bool isHorizontal);
	private:
		bool mbIsHorizontal;
	};
}