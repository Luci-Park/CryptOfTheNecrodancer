#include "LGameCharacter.h"
#include "LBeatManager.h"
#include "LMapManager.h"
#include "LCharacterSprite.h"
#include "LTime.h"
namespace cl
{
	GameCharacter::GameCharacter(Scene* sc, bool isFlying)
		: TileObject(sc)
		, mMoveTarget(Vector2::Zero)
		, mSprite(nullptr)
		, mbIsMoving(false)
		, mbIsFlying(isFlying)
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
				if (!mbIsFlying)
					MapManager::OnTileStep(this, mIndex);
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
	void GameCharacter::Interact(TileObject* object)
	{
		if (object != nullptr)
			object->Attack(this, mIndex);
	}
	void GameCharacter::Sink()
	{
		mSprite->Sink();
		mbIsSinked = true;
	}
}