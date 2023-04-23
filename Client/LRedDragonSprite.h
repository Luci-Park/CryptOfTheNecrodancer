#pragma once
#include "LCharacterSprite.h"
#include "LDragonBase.h"
namespace cl
{
	class RedDragonSprite : public CharacterSprite
	{
	public:
		RedDragonSprite(Scene* sc);
		virtual ~RedDragonSprite();

		void SetDragonState(DragonBase::State state);

		virtual void Initialize() override;
		virtual void Turn(Vector2 dir);
	private:
		int GetIndex(Vector2 dir);
		void PlayAnimation();
	private:
		std::wstring mAnimations[3][2];
		std::wstring mShadowAnimations[3][2];
		DragonBase::State mDragonState;
		Vector2 mLookDir;
	};
}
