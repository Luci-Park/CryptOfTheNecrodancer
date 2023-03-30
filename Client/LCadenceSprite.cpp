#include "LCadenceSprite.h"
#include "LCadenceHead.h"
#include "LCadenceBody.h"
#include "LObject.h"
#include "LBeatManager.h"
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
		mBody = object::Instantiate<CadenceBody>(GameObject::GetScene(), GameObject::mTransform, GameObject::mTransform->GetPos(), eLayerType::Foreground);
		mHead = object::Instantiate<CadenceHead>(GameObject::GetScene(), GameObject::mTransform, GameObject::mTransform->GetPos(), eLayerType::Foreground);
	}
	void CadenceSprite::Update()
	{
		CharacterSprite::Update();
	}
	void CadenceSprite::Render(HDC hdc)
	{
		CharacterSprite::Render(hdc);
		mBody->Render(hdc);
		mHead->Render(hdc);
	}
	void CadenceSprite::Turn(Vector2 dir)
	{
		mHead->Flip(dir);
		mBody->Flip(dir);
	}
	void CadenceSprite::OnBeatChanged()
	{
		float dur = BeatManager::BeatDuration();
		mHead->SetDuration(dur);
		mBody->SetDuration(dur);
	}
}