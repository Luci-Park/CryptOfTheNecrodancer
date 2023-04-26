#pragma once
#include "LCharacterSprite.h"
namespace cl
{
	class BishopSprite : public CharacterSprite
	{
	public:
		enum class State {Idle, Ready};
		BishopSprite(Scene* sc);
		~BishopSprite() {};

		virtual void Initialize() override;

		virtual void Turn(Vector2 dir) override;
		virtual void OnBeatChanged();
		void Ready();
		void Idle();
	private:
		std::wstring mReady;
		std::wstring mIdle;
		std::wstring mShadowReady;
		std::wstring mShadowIdle;
		State mState;
	};
}

