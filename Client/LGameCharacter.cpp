#include "LGameCharacter.h"
#include "LCharacterSprite.h"
#include "LTime.h"
namespace cl
{
	GameCharacter::GameCharacter(Scene* sc)
		: GameObject(sc, false)
		, mGameManager(nullptr)
		, mMoveTarget(Vector2::Zero)
		, mSprite(nullptr)
	{
	}
	GameCharacter::~GameCharacter()
	{
		mSprite = nullptr;
		mGameManager = nullptr;
	}
	void GameCharacter::Initialize()
	{
		mMoveTarget = mTransform->GetPos();
		mSprite->SetManager(mGameManager);
		GameObject::Initialize();
	}
	void GameCharacter::Update()
	{		
		mTransform->SetPos(Vector2::MoveTowards(mTransform->GetPos(), mMoveTarget, mGameManager->MoveSpeed() * Time::DeltaTime()));
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
	void GameCharacter::Release()
	{
		GameObject::Release();
	}
	void GameCharacter::SetManager(GameManager* m)
	{ 
		mGameManager = m;
		mSprite->SetManager(m);
	}
	void GameCharacter::OnBeatChanged()
	{
		mSprite->OnBeatChanged();
	}
}