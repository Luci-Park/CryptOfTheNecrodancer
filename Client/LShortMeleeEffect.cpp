#include "LShortMeleeEffect.h"
#include "LAnimator.h"
namespace cl
{
	ShortMeleeEffect::ShortMeleeEffect(Scene* sc)
		:WeaponEffect(sc)
	{
	}
	ShortMeleeEffect::~ShortMeleeEffect()
	{
	}
	void ShortMeleeEffect::Initialize()
	{
		WeaponEffect::Initialize();
		mUpAnim = L"Dagger_Up";
		mDownAnim = L"Dagger_Down";
		mRightAnim = L"Dagger_Right";
		mLeftAnim = L"Dagger_Left";
		mAnimator->CreateAnimation(mUpAnim, mUpAnim, L"..\\Assets\\Arts\\Effects\\AttackSwipes\\Dagger\\Dagger_Up.bmp",
			1, 3, 0, 0, 3, Vector2::Zero, 0.25);
		mAnimator->CreateAnimation(mDownAnim, mDownAnim, L"..\\Assets\\Arts\\Effects\\AttackSwipes\\Dagger\\Dagger_Down.bmp",
			1, 3, 0, 0, 3, Vector2::Zero, 0.25);
		mAnimator->CreateAnimation(mRightAnim, mRightAnim, L"..\\Assets\\Arts\\Effects\\AttackSwipes\\Dagger\\Dagger_Right.bmp",
			3, 1, 0, 0, 3, Vector2::Zero, 0.25);
		mAnimator->CreateAnimation(mLeftAnim, mLeftAnim, L"..\\Assets\\Arts\\Effects\\AttackSwipes\\Dagger\\Dagger_Left.bmp",
			3, 1, 0, 0, 3, Vector2::Zero, 0.25);
	}

	void ShortMeleeEffect::PlayUp()
	{
		mTransform->SetLocalPos(Vector2::Up * UNITLENGTH);
		mAnimator->Play(mUpAnim, Animator::PlaySetting::Once, true);
	}

	void ShortMeleeEffect::PlayDown()
	{
		mTransform->SetLocalPos(Vector2::Down * UNITLENGTH);
		mAnimator->Play(mDownAnim, Animator::PlaySetting::Once, false);
	}

	void ShortMeleeEffect::PlayRight()
	{
		mTransform->SetLocalPos(Vector2::Right * UNITLENGTH);
		mAnimator->Play(mRightAnim, Animator::PlaySetting::Once, false);
	}

	void ShortMeleeEffect::PlayLeft()
	{
		mTransform->SetLocalPos(Vector2::Left * UNITLENGTH);
		mAnimator->Play(mLeftAnim, Animator::PlaySetting::Once, true);
	}

}