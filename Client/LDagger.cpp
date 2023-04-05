#include "LDagger.h"
#include "LAnimator.h"
#include "LTileObject.h"
#include "LMapManager.h"
namespace cl
{
	Dagger::Dagger(Scene* sc)
		:Weapon(sc)
	{
		mPower = 1;
	}

	Dagger::~Dagger()
	{
	}

	void Dagger::SetAnimation()
	{
		mUpAnimation = L"Dagger_Up";
		mDownAnimation = L"Dagger_Down";
		mLeftAnimation = L"Dagger_Left";
		mRightAnimation = L"Dagger_Right";
		mAnimator->CreateAnimation(mRightAnimation, L"Dagger_Right", L"..\\Assets\\Arts\\Effects\\AttackSwipes\\Dagger_Right.bmp",
			3, 1, 0, 0, 3, Vector2::Zero, 0.25);
		mAnimator->CreateAnimation(mLeftAnimation, L"Dagger_Left", L"..\\Assets\\Arts\\Effects\\AttackSwipes\\Dagger_Left.bmp",
			3, 1, 0, 0, 3, Vector2::Zero, 0.25);
		mAnimator->CreateAnimation(mUpAnimation, L"Dagger_Up", L"..\\Assets\\Arts\\Effects\\AttackSwipes\\Dagger_Up.bmp",
			1, 3, 0, 0, 3, Vector2::Zero, 0.25);
		mAnimator->CreateAnimation(mDownAnimation, L"Dagger_Down", L"..\\Assets\\Arts\\Effects\\AttackSwipes\\Dagger_Down.bmp",
			1, 3, 0, 0, 3, Vector2::Zero, 0.25);
		OnBeatChanged();
	}

	Vector2 Dagger::EffectPos(Vector2 dir)
	{
		return dir * UNITLENGTH;
	}

	std::wstring Dagger::SelectAnimation(Vector2 dir)
	{
		if (dir == Vector2::Right)
			return mRightAnimation;
		if (dir == Vector2::Left)
			return mLeftAnimation;
		if (dir == Vector2::Up)
			return mUpAnimation;
		if (dir == Vector2::Down)
			return mDownAnimation;
		return std::wstring();
	}

	bool Dagger::TryAttack(Vector2 srcIdx, Vector2 input)
	{
		Vector2 dest = srcIdx + input;
		TileObject* enemy = MapManager::GetEnemy(dest);
		if (enemy != nullptr)
		{
			enemy->OnAttacked(mPower);
			return true;
		}
		return false;
	}

}
