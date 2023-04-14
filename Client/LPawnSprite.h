#pragma once
#include "LCharacterSprite.h"
namespace cl
{
	class PawnSprite : public CharacterSprite
	{
	public:
		PawnSprite(Scene* sc);
		~PawnSprite() {};

		virtual void Initialize() override;

		virtual void Turn(Vector2 dir) override {};
		void Ready();
		void Idle();
	private:
		std::wstring mReady;
		std::wstring mIdle;

	};
}