#pragma once
#include "LCharacterSprite.h"
#include "LMinotaurBase.h"
namespace cl
{
	class MinotaurSprite : public CharacterSprite
	{
	public:
		MinotaurSprite(Scene* sc);
		virtual ~MinotaurSprite();

		void SetMinoState(MinotaurBase::State state);
		void SetY(int y);
		
		virtual void Initialize() override;
		virtual void Turn(Vector2 dir);
	private:
		int GetIndex(Vector2 dir);
		void PlayAnimation();
	private:
		std::wstring mAnimations[3][2];
		std::wstring mShadowAnimations[3][2];
		MinotaurBase::State mMinoState;
		Vector2 mLookDir;
	};
}

