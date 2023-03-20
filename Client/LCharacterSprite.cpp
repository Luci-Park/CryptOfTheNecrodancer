#include "LCharacterSprite.h"
namespace cl
{
	CharacterSprite::CharacterSprite(Scene *sc)
		: GameObject(sc, false)
		, mGameManager(nullptr)
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
		GameObject::Update();
	}
	void CharacterSprite::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void CharacterSprite::Release()
	{
		GameObject::Release();
	}
	void CharacterSprite::Jump()
	{
	}
}
