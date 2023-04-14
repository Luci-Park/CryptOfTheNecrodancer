#pragma once
#include "LCharacterSprite.h"
namespace cl
{
	class BishopSprite : public CharacterSprite
	{
	public:
		BishopSprite(Scene* sc);
		~BishopSprite() {};

		virtual void Initialize() override;

		virtual void Turn(Vector2 dir) override {};
		void Ready();
		void Idle();
	private:
		std::wstring mReady;
		std::wstring mIdle;
	};
}

