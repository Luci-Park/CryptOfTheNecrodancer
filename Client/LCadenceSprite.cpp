#include "LCadenceSprite.h"
#include "LCadenceHead.h"
#include "LCadenceBody.h"
#include "LObject.h"
namespace cl
{
	CadenceSprite::CadenceSprite(Scene* sc)
		: CharacterSprite(sc)
		, mHead(nullptr), mBody(nullptr)
	{
	}
	CadenceSprite::~CadenceSprite()
	{
	}
	void CadenceSprite::Initialize()
	{
		CharacterSprite::Initialize();
		mBody = object::Instantiate<CadenceBody>(GameObject::GetScene(), GameObject::mTransform, GameObject::mTransform->GetPos(), eLayerType::Player);
		mHead = object::Instantiate<CadenceHead>(GameObject::GetScene(), GameObject::mTransform, GameObject::mTransform->GetPos(), eLayerType::Player);
	}
	void CadenceSprite::Update()
	{
		CharacterSprite::Update();
	}
	void CadenceSprite::Render(HDC hdc)
	{
		CharacterSprite::Render(hdc);
	}
	void CadenceSprite::Release()
	{
		mHead = nullptr;
		mBody = nullptr;
		CharacterSprite::Release();
	}
	void CadenceSprite::Turn(Vector2 dir)
	{
		mHead->Flip(dir);
		mBody->Flip(dir);
	}
	void CadenceSprite::OnBeatChanged()
	{
		float dur = mGameManager->BeatDuration();
		mHead->SetDuration(dur);
		mBody->SetDuration(dur);
	}
}