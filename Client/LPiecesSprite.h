#pragma once
#include "LCharacterSprite.h"
namespace cl
{
	class PiecesSprite : public CharacterSprite
	{
	public:
		enum class State{Idle, Ready};
		PiecesSprite(Scene* sc);
		~PiecesSprite(){}

		virtual void Initialize() override;
		virtual void Turn(Vector2 dir) override;
		virtual void OnBeatChanged() override; 
		void Ready();
		void Idle();
	protected:
		std::wstring mReady;
		std::wstring mIdle;
		std::wstring mShadowReady;
		std::wstring mShadowIdle;
		State mState;
	};
}

