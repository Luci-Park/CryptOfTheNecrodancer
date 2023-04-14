#pragma once
#include "LCharacterSprite.h"
namespace cl
{
	class KnightSprite : public CharacterSprite
	{
	public:
		KnightSprite(Scene* sc);
		~KnightSprite() {};

		virtual void Initialize() override;

		virtual void Turn(Vector2 dir) override {};
		void Ready();
		void Idle();
	private:
		std::wstring mReady;
		std::wstring mIdle;

	};
}

