#include "LAnimatorChecker.h"
#include "LAnimator.h"
namespace cl
{
	AnimatorChecker::AnimatorChecker(Scene* scene)
		:GameObject(scene, false)
	{
		mTransform->SetScale(Vector2::One * UNITSCALE);
	}
	AnimatorChecker::~AnimatorChecker()
	{
	}
	void AnimatorChecker::Initialize()
	{
		std::wstring aniName = L"";
		std::wstring sheetName = L"";
		std::wstring sheetPath = L"";
		Vector2 leftTop {0, 2};
		Vector2 size{ 0, 2 };
		UINT spriteLength = 0;
		Animator* animator = AddComponent<Animator>();
		animator->CreateAnimation(aniName, sheetName, sheetPath, leftTop, size, spriteLength, 1.0f);
		animator->Play(aniName, true, false);
	}
}