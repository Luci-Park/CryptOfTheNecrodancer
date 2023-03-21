#include "LCadenceSprite.h"
#include "LCadenceHead.h"
#include "LCadenceBody.h"
#include "LObject.h"
#include "LGameManager.h"
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
	void CadenceSprite::Turn(Vector2 dir)
	{
		mHead->Flip(dir);
		mBody->Flip(dir);
	}
	void CadenceSprite::OnBeatChanged()
	{
		float dur = GameManager::BeatDuration() * 0.5;
		mHead->SetDuration(dur);
		mBody->SetDuration(dur);
	}
}