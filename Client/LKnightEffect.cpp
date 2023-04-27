#include "LKnightEffect.h"
#include "LAnimator.h"
namespace cl
{
	KnightEffect::KnightEffect(Scene* sc)
		:WeaponEffect(sc)
	{
	}
	KnightEffect::~KnightEffect()
	{
	}
	void KnightEffect::Initialize()
	{
		WeaponEffect::Initialize();
		std::wstring path = L"..\\Assets\\Arts\\Effects\\AttackSwipes\\KnightAttack\\";
		mAttackAnimation[(int)Knight::AttackDir::DownLeft] = L"DownLeft";
		mAttackAnimation[(int)Knight::AttackDir::DownRight] = L"DownRight";
		mAttackAnimation[(int)Knight::AttackDir::LeftDown] = L"LeftDown";
		mAttackAnimation[(int)Knight::AttackDir::LeftUp] = L"LeftUp";
		mAttackAnimation[(int)Knight::AttackDir::RightDown] = L"RightDown";
		mAttackAnimation[(int)Knight::AttackDir::RightUp] = L"RightUp";
		mAttackAnimation[(int)Knight::AttackDir::UpLeft] = L"UpLeft";
		mAttackAnimation[(int)Knight::AttackDir::UpRight] = L"UpRight";
		for (int i = 0; i < (int)Knight::AttackDir::Size; ++i)
		{
			mAnimator->CreateAnimation(mAttackAnimation[i], L"Knight" + mAttackAnimation[i]
				, path + mAttackAnimation[i] + L".bmp", 1, 1, 0, 0, 1, Vector2::Zero, BeatManager::BeatDuration() * 0.25);
		}
	}
	void KnightEffect::PlayEffect(Vector2 direction)
	{
		Knight::AttackDir dir = Knight::GetDir(direction);
		if (dir != Knight::AttackDir::Size)
		{
			if (abs(direction.x) > abs(direction.y))
			{
				mTransform->SetLocalPos(Vector2(direction.x * 0.5f, 0.0) * UNITLENGTH);
			}
			else
			{
				mTransform->SetLocalPos(Vector2(0.0, direction.y * 0.5f) * UNITLENGTH);
			}
			mAnimator->Play(mAttackAnimation[(int)dir], Animator::PlaySetting::Once, false);
		}
	}
}