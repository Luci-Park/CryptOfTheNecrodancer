#include "LGameCharacter.h"
#include "LBeatManager.h"
#include "LMapManager.h"
#include "LCharacterSprite.h"
#include "LTime.h"
namespace cl
{
	GameCharacter::GameCharacter(Scene* sc, bool isTouchingGround)
		: TileObject(sc)
		, mMoveTarget(Vector2::Zero)
		, mSprite(nullptr)
		, mbIsMoving(false)
		, mbIsTouchingGround(isTouchingGround)
		, mbMoveFailed(false)
	{
	}
	GameCharacter::~GameCharacter()
	{
	}
	void GameCharacter::Initialize()
	{
		TileObject::Initialize();
		mMoveTarget = mTransform->GetPos();
	}
	void GameCharacter::Update()
	{		
		mTransform->SetPos(Vector2::MoveTowards(mTransform->GetPos(), mMoveTarget, BeatManager::MoveSpeed() * 2 * Time::DeltaTime()));
		if (Vector2::Distance(mTransform->GetPos(), mMoveTarget) <= 0.01f)
		{
			if (mbIsMoving)
			{
				mbIsMoving = false;
				mSprite->Reset();
				if (mbMoveFailed)
				{
					Recoil(prevDir);
				}
				else {
					if (mbIsTouchingGround)
						MapManager::OnTileStep(this, mIndex);
				}
			}
		}
		else {
			mbIsMoving = true;
		}
		TileObject::Update();
	}
	void GameCharacter::Render(HDC hdc)
	{
		TileObject::Render(hdc);
		if (mSprite != nullptr)
			mSprite->Render(hdc);
	}
	
	void GameCharacter::OnBeatChanged()
	{
		if(mSprite != nullptr)
			mSprite->OnBeatChanged();
	}
	void GameCharacter::Recoil(Vector2 dir)
	{
		if (!mbMoveFailed)
		{
			mMoveTarget += dir * UNITLENGTH / 2;
			mbMoveFailed = true;
			prevDir = dir;
		}
		else
		{
			mMoveTarget -= dir * UNITLENGTH / 2;
			mSprite->Jump();
			mbMoveFailed = false;
		}
	}
	void GameCharacter::Sink()
	{
		mSprite->Sink();
		mbIsSinked = true;
	}
	bool GameCharacter::UnSink()
	{
		if (mbIsSinked)
		{
			mbIsSinked = false;
			mSprite->UnSink();
			return true;
		}
		return false;
	}
	void GameCharacter::OnAttacked(float attackPower, Vector2 dir)
	{
		mHealth -= attackPower;
		if (mHealth > 0)
		{
			PlayOnHitSound();
		}
		else
		{
			PlayOnDeathSound();
			OnDestroy();
			return;
		}			
	}
}