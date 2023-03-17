#pragma once
#include "LEntity.h"
#include "LSprite.h"
namespace cl
{
	class Animator;
	class Image;
	class Animation : public Entity
	{
	public:
		Animation();
		~Animation();

		void Initialize();
		void Update();
		void Render(HDC hdc);
		void Create(Image* sheet, UINT coulmn, UINT row, UINT sCol, UINT sRow, UINT spriteLength, Vector2 offset, float duration);
		void Reset();

		bool IsComplete() { return mbComplete; }
		void SetAnimator(Animator* animator) { mAnimator = animator; }
		void SetDuration(float duration) { mDuration = duration / mSpriteSheet.size(); }

	private:
		Animator* mAnimator;
		Image* mSheetImage;
		std::vector<Sprite> mSpriteSheet;
		float mTime;
		float mDuration;
		bool mbComplete;
		int mSpriteIndex;
	};
}
