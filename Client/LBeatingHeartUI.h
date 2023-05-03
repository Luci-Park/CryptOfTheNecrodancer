#pragma once
#include "LGameObject.h"
#include "LBeatObject.h"
#include "LSprite.h"
namespace cl
{
	class SpriteRenderer;
	class BeatingHeartUI : public GameObject, public BeatObject
	{
	public:
		BeatingHeartUI(Scene* sc);
		virtual ~BeatingHeartUI();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnBeat();
		virtual void OnLateBeat() {}
		virtual void OnBeatChanged(){}
	private:
		SpriteRenderer* mSpriteRenderer;
		Sprite mSmallHeart;
		Sprite mBigHeart;
		bool mbIsBeating;
		float mTimer;
		float mBeatTime;
	};

}

