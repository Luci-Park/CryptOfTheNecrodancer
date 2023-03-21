#include "LGameCharacter.h"
#include "LCharacterSprite.h"
#include "LTime.h"
namespace cl
{
	GameCharacter::GameCharacter(Scene* sc)
		: GameObject(sc, false)
		, mMoveTarget(Vector2::Zero)
		, mSprite(nullptr)
	{
	}
	GameCharacter::~GameCharacter()
	{
	}
	void GameCharacter::Initialize()
	{
		GameObject::Initialize();
		mMoveTarget = mTransform->GetPos();
	}
	void GameCharacter::Update()
	{		
		mTransform->SetPos(Vector2::MoveTowards(mTransform->GetPos(), mMoveTarget, GameManager::MoveSpeed() * 2 * Time::DeltaTime()));
		if (Vector2::Distance(mTransform->GetPos(), mMoveTarget) <= 0.01f)
		{
			Move();
		}
		GameObject::Update();
	}
	void GameCharacter::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void GameCharacter::OnBeatChanged()
	{
		mSprite->OnBeatChanged();
	}
}