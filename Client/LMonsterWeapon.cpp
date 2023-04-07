#include "LMonsterWeapon.h"
#include "LAnimator.h"
#include "LTileObject.h"
#include "LMapManager.h"
#include "LCadence.h"
namespace cl
{
	MonsterWeapon::MonsterWeapon(Scene* sc)
		:Weapon(sc)
	{
	}

	MonsterWeapon::~MonsterWeapon()
	{
	}

	void MonsterWeapon::SetSprite()
	{
	}

	void MonsterWeapon::SetAnimation()
	{
		mUpAnimation = L"Enemy_Up";
		mDownAnimation = L"Enemy_Down";
		mLeftAnimation = L"Enemy_Left";
		mRightAnimation = L"Enemy_Right";
		mAnimator->CreateAnimation(mRightAnimation, mRightAnimation, L"..\\Assets\\Arts\\Effects\\AttackSwipes\\Enemy\\Enemy_Right.bmp",
			5, 1, 0, 0, 3, Vector2::Zero, 0.25);
		mAnimator->CreateAnimation(mLeftAnimation, mLeftAnimation, L"..\\Assets\\Arts\\Effects\\AttackSwipes\\Enemy\\Enemy_Left.bmp",
			5, 1, 0, 0, 3, Vector2::Zero, 0.25);
		mAnimator->CreateAnimation(mUpAnimation, mUpAnimation, L"..\\Assets\\Arts\\Effects\\AttackSwipes\\Enemy\\Enemy_Up.bmp",
			1, 5, 0, 0, 3, Vector2::Zero, 0.25);
		mAnimator->CreateAnimation(mDownAnimation, mDownAnimation, L"..\\Assets\\Arts\\Effects\\AttackSwipes\\Enemy\\Enemy_Down.bmp",
			1, 5, 0, 0, 3, Vector2::Zero, 0.25);
		OnBeatChanged();
	}

	Vector2 MonsterWeapon::EffectPos(Vector2 dir)
	{
		return dir * UNITLENGTH;
	}

	std::wstring MonsterWeapon::SelectAnimation(Vector2 dir)
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

	bool MonsterWeapon::TryAttack(Vector2 srcIdx, Vector2 input)
	{
		Vector2 dest = srcIdx + input;
		Cadence* enemy = MapManager::GetPlayer(dest);
		if (enemy != nullptr)
		{
			enemy->OnAttacked(mPower);
			return true;
		}
		return false;
	}

}
