#pragma once
#include "LSprite.h"
#include "LItem.h"
namespace cl
{
	class WallTile;
	class AudioClip;
	class Tool : public Item
	{
	public:
		Tool(Scene* sc);
		virtual ~Tool(){}

		void Initialize() override;

		virtual bool Dig(WallTile* object);
	protected:
		virtual void SetSprite() = 0;
	protected:
		int mDigPower;
		AudioClip* mDigFailedClip;
	};

	class Shovel : public Tool
	{
	public:
		Shovel(Scene* sc);
		virtual ~Shovel();
	protected:
		virtual void SetSprite() override;
	};

	class PickAxe : public Tool
	{
	public:
		PickAxe(Scene* sc);
		virtual ~PickAxe();

		virtual bool Dig(WallTile* object) override;
	protected:
		virtual void SetSprite() override;
	};
}

