#pragma once
#include "LGameObject.h"
#include "LSpriteRenderer.h"
namespace cl
{
	class SpriteRenderer;
	class Cadence;
	class AudioClip;
	//is responsible for the sprite and interaction of map and player
	class Item : public GameObject
	{
	public:
		Item(Scene* sc, eItemTypes type);
		virtual ~Item();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC hdc) override;

		virtual void PickUpItem(Cadence* player);
		virtual void SetItem(Vector2 pos);
		virtual bool Use(Cadence* player) = 0;

		SpriteRenderer* GetSpriteRenderer() { return mSpriteRenderer; }
	protected:
		virtual void SetSprite() = 0;
	protected:
		bool mbIsSetDown;
		eItemTypes mType;
		SpriteRenderer* mSpriteRenderer;
		AudioClip* mGetItemClip;
	};
}

