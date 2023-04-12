#pragma once
#include "LCharacterSprite.h"
namespace cl
{
	class SkeletonSprite : public CharacterSprite
	{
	public:
		SkeletonSprite(Scene* sc);
		~SkeletonSprite() {};

		virtual void Initialize() override;

		virtual void Turn(Vector2 dir) override;
		void SetSkeleY(int y);
		void Idle();
		void RaiseHand();
		void LostHead();
	protected:
		int skeleY;
	private:
		int GetIndex(Vector2 dir);
	private:
		Vector2 mLookDir;
		std::wstring idleAnimation[3];
		std::wstring raiseHandAnimation[3];
		std::wstring noHead;
		bool mbLostHead;
	};
}