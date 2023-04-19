#pragma once
#include "LCharacterSprite.h"
namespace cl
{
	class SkeletonSprite : public CharacterSprite
	{
	public:
		enum class Status
		{
			RaiseHand, Idle, NoHead
		};
		SkeletonSprite(Scene* sc);
		~SkeletonSprite() {};

		virtual void Initialize() override;

		virtual void Turn(Vector2 dir) override;
		virtual void PlayAnimation() override;
		void SetSkeleY(int y);
		void Idle();
		void RaiseHand();
		void LostHead();

	private:
		int GetIndex(Vector2 dir);

	private:
		int skeleY;
		Vector2 mLookDir;
		std::wstring mIdleAnimation[2];
		std::wstring mIdleShadowAnimation[2];
		std::wstring mRaiseHandAnimation[2];
		std::wstring mHandShadowAnimation[2];
		std::wstring mNoHead;
		std::wstring mNoHeadShadow;
		Status mStatus;
	};
}