#include "LGameCharacter.h"
#include "LBeatManager.h"
#include "LCharacterSprite.h"
#include "LTime.h"
namespace cl
{
	GameCharacter::GameCharacter(Scene* sc)
		: TileObject(sc)
		, mMoveTarget(Vector2::Zero)
		, mSprite(nullptr)
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
			Move();
		}
		TileObject::Update();
	}
	void GameCharacter::Render(HDC hdc)
	{
		TileObject::Render(hdc);
	}
	void GameCharacter::OnBeatChanged()
	{
		mSprite->OnBeatChanged();
	}
}