#include "LCharacterSprite.h"
#include "LTime.h"
namespace cl
{
	CharacterSprite::CharacterSprite(Scene *sc)
		: GameObject(sc, false)
		, mGameManager(nullptr)
		, mbDirIsUp(true)
		, mbIsJumping(false)
	{
	}
	CharacterSprite::~CharacterSprite()
	{
		mGameManager = nullptr;
	}
	void CharacterSprite::Initialize()
	{
		GameObject::Initialize();
	}
	void CharacterSprite::Update()
	{
		if (mbIsJumping)
			Jump();
		GameObject::Update();
	}
	void CharacterSprite::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void CharacterSprite::Jump()
	{
		if (!mbIsJumping)
		{
			mbIsJumping = true;
			return;
		}
		Vector2 target = mbDirIsUp ? Vector2::Up * mGameManager->Displacement() * 0.5 : Vector2::Zero;
		if (Vector2::Distance(mTransform->GetLocalPos(), target) < 0.01f)
		{
			mbDirIsUp = !mbDirIsUp;
			if (mbDirIsUp) mbIsJumping = false;
		}
		mTransform->SetLocalPos(Vector2::MoveTowards(mTransform->GetLocalPos(), target, mGameManager->MoveSpeed() * Time::DeltaTime()));
	}
}
