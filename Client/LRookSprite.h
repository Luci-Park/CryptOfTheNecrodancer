#pragma once
#include "LCharacterSprite.h"
namespace cl
{
	class RookSprite : public CharacterSprite
	{
	public:
		RookSprite(Scene* sc);
		~RookSprite() {};

		virtual void Initialize() override;

		virtual void Turn(Vector2 dir) override {};
		void Ready();
		void Idle();
	private:
		std::wstring mReady;
		std::wstring mIdle;

	};
}

