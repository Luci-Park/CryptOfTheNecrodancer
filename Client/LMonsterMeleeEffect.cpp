#include "LMonsterMeleeEffect.h"
#include "LAnimator.h"
#include "LBeatManager.h"
namespace cl
{
	
	MonsterMeleeEffect::MonsterMeleeEffect(Scene* sc)
		:WeaponEffect(sc)
	{
	}
	MonsterMeleeEffect::~MonsterMeleeEffect()
	{
	}
	void MonsterMeleeEffect::Initialize()
	{
		WeaponEffect::Initialize();
		mUpAnim = L"Enemy_Up";
		mDownAnim = L"Enemy_Down";
		mRightAnim = L"Enemy_Right";
		mLeftAnim = L"Enemy_Left";
		mAnimator->CreateAnimation(mRightAnim, mRightAnim, L"..\\Assets\\Arts\\Effects\\AttackSwipes\\Enemy\\Enemy_Right.bmp",
			5, 1, 0, 0, 3, Vector2::Zero, BeatManager::BeatDuration() * 0.25);
		mAnimator->CreateAnimation(mLeftAnim, mLeftAnim, L"..\\Assets\\Arts\\Effects\\AttackSwipes\\Enemy\\Enemy_Left.bmp",
			5, 1, 0, 0, 3, Vector2::Zero, BeatManager::BeatDuration() * 0.25);
		mAnimator->CreateAnimation(mUpAnim, mUpAnim, L"..\\Assets\\Arts\\Effects\\AttackSwipes\\Enemy\\Enemy_Up.bmp",
			1, 5, 0, 0, 3, Vector2::Zero, BeatManager::BeatDuration() * 0.25);
		mAnimator->CreateAnimation(mDownAnim, mDownAnim, L"..\\Assets\\Arts\\Effects\\AttackSwipes\\Enemy\\Enemy_Down.bmp",
			1, 5, 0, 0, 3, Vector2::Zero, BeatManager::BeatDuration() * 0.25);
	}

	void MonsterMeleeEffect::PlayUp()
	{
		mTransform->SetLocalPos(Vector2::Up * UNITLENGTH);
		mAnimator->Play(mUpAnim, Animator::PlaySetting::Once, true);
	}

	void MonsterMeleeEffect::PlayDown()
	{
		mTransform->SetLocalPos(Vector2::Down * UNITLENGTH);
		mAnimator->Play(mDownAnim, Animator::PlaySetting::Once, false);
	}

	void MonsterMeleeEffect::PlayRight()
	{
		mTransform->SetLocalPos(Vector2::Right * UNITLENGTH);
		mAnimator->Play(mRightAnim, Animator::PlaySetting::Once, false);
	}

	void MonsterMeleeEffect::PlayLeft()
	{
		mTransform->SetLocalPos(Vector2::Left * UNITLENGTH);
		mAnimator->Play(mLeftAnim, Animator::PlaySetting::Once, true);
	}
}